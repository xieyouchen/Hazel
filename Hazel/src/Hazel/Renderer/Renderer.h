#pragma once
#include "Hazel/Renderer/VertexArray.h"

#include <glm/glm.hpp>

#include "OrthographicCamera.h"

#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>

#include "RendererAPI.h"


namespace Hazel {
	class Renderer {
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader> shader, 
			const std::shared_ptr<VertexArray>& vertexArray,
			const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
