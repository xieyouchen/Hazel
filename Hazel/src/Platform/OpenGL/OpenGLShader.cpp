#include "hzpch.h"
#include "OpenGLShader.h"

#include <Glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel {

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex"){
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel") {
			return GL_FRAGMENT_SHADER;
		}
		HZ_CORE_ASSERT(false, "Unknown shader type.");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

		CompileShader(shaderSources);
	}


	OpenGLShader::OpenGLShader(const std::string& path)
	{
		std::string source = ReadFile(path);
		HZ_CORE_ASSERT(!source.empty(), "string is null from GLSL.");
		auto shaderSources = SplitShaderFromSourceFile(source);
		CompileShader(shaderSources);
		/*
		support file path:
		 asserts\shaders\Texture.glsl
		 asserts/shaders/Texture.glsl
		 Texture.glsl
		 */
		auto lastSlash = path.find_last_of("/\\");
		auto nameBeg = lastSlash != std::string::npos ? lastSlash + 1 : 0;
		auto lastDot = path.rfind(".");
		m_Name = lastDot != std::string::npos
			? path.substr(nameBeg, lastDot - nameBeg)
			: path.substr(nameBeg, path.size() - nameBeg);

	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::string fileContent;
		std::ifstream in(path, std::ios::in, std::ios::binary);

		if (in) {
			in.seekg(0, std::ios::end);
			fileContent.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&fileContent[0], fileContent.size());
		}
		else {
			HZ_CORE_ERROR("Could not open the file: {0}", path);
		}

		return fileContent;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::SplitShaderFromSourceFile(const std::string source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		std::string typeToken = "#type";
		size_t typeTokenLen = typeToken.size();
		size_t typeLinePos = source.find(typeToken, 0); // 有token的

		size_t nextShaderLinePos = typeLinePos;
		while (nextShaderLinePos != std::string::npos) {
			size_t typeLineEndPos = source.find_first_of("\n", nextShaderLinePos);
			HZ_CORE_ASSERT(typeLineEndPos != std::string::npos, "Read shader file failed."); // 这里是默认文件的每一行以换行为结尾
			//if (currLineEndPos == std::string::npos) {
			//	currLineEndPos = source.size();
			//} // 这样其实可以保证最后一行如果不是换行/回车结尾，也没有关系
			size_t type_begin = nextShaderLinePos + typeTokenLen + 1; // 从 vertex / fragment / pixel 开始
			nextShaderLinePos = source.find(typeToken, typeLineEndPos); // 包含 type 的整个 shader 模块
			std::string type = source.substr(type_begin, typeLineEndPos - type_begin);
			HZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type.");

			size_t shaderLinePos = source.find_first_not_of("\r\n", typeLineEndPos);


			shaderSources[ShaderTypeFromString(type)] =
				nextShaderLinePos != std::string::npos
				? source.substr(shaderLinePos, nextShaderLinePos - shaderLinePos)
				: source.substr(shaderLinePos);

		}

		return shaderSources;
	}

	void OpenGLShader::CompileShader(const std::unordered_map<GLenum, std::string> shaderSource)
	{
		GLuint program = glCreateProgram();
		std::array<GLenum, 2> glShaderIDs;
		size_t glShaderIDsIndex = 0;
		for (auto &kv : shaderSource) {
			GLenum type = kv.first;
			std::string source = kv.second;
			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			glCompileShader(shader);
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);

				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);

				HZ_CORE_ERROR("{0}", infoLog.data());
				HZ_CORE_ASSERT(false, "Shader compile failed.");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDsIndex++] = shader;
		}
		m_RendererID = program;

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(program);

			for (auto id : glShaderIDs) {
				glDeleteShader(id);
			}

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Shader link failed.");
			return;
		}

		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
		}
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteShader(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}