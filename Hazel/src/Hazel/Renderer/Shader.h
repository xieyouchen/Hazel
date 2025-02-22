#pragma once
#include <string>

#include <glm/glm.hpp>

namespace Hazel {
	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		
		void UploadUniformFloat4(const std::string& name, const glm::vec4& color);

		inline const uint32_t GetRendererID() const { return m_RendererID; }

	private:
		uint32_t m_RendererID;
	};
}