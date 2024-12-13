#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {
	struct WindowProps { // 窗口初始化配置项
		std::string Title;
		unsigned int Width, Height;
		WindowProps(const std::string& title = "Hazel Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};
	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}  // 和 virtual ~Window(); 有什么区别
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		// 在 Window 父类声明静态的创建函数
		static Window* Create(const WindowProps& props = WindowProps());
	};
}


