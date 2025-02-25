#include "hzpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel {
	RendererAPI::API RendererAPI::s_API = API::OpenGL;

	RendererAPI* RendererAPI::Create()
	{
		switch (s_API) {
			case API::None:    HZ_CORE_ASSERT(false, "None is currently not supported!");
			case API::OpenGL:  return new OpenGLRendererAPI();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}