#pragma once
#include "Hazel/Renderer/Buffer.h"

namespace Hazel {
	class VertexArray {
	public:
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexArray* Create();

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) = 0;

		inline virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
		inline virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

	};
}
