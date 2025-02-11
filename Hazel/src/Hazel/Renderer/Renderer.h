#pragma once
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel {
	class Renderer {
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	};
}
