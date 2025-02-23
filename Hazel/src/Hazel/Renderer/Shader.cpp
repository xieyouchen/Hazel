#include "hzpch.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {

	Shader::~Shader()
	{

	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		return new OpenGLShader(vertexSrc, fragmentSrc);
	}
}