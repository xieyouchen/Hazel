#include "hzpch.h"
#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {

	Hazel::VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		return new OpenGLVertexBuffer(vertices, size); 
	}

	Hazel::IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		return new OpenGLIndexBuffer(indices, size * sizeof(uint32_t));
	}

}