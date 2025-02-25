#pragma once

#include <memory>

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		//#define HAZEL_API __declspec(dllexport)
		#define HAZEL_API
	#else
		//#define HAZEL_API __declspec(dllimport)
		//#define IMGUI_API __declspec(dllimport) // ���ӵ���
		#define HAZEL_API
		#define IMGUI_API
	#endif
#else
	#error Hazel only support Windows!
#endif

#if HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif

#ifdef HZ_ENABLE_ASSERTS
	#define	HZ_ASSERT(x, ...) {if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}