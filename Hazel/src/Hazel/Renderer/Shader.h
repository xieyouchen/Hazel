#pragma once
#include <string>

#include <glm/glm.hpp>

namespace Hazel {
	class Shader {
	public:
		virtual ~Shader();

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}