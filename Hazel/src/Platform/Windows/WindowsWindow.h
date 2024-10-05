#pragma once
#include "Hazel/Window.h"
#include "glad/glad.h"

#include "GLFW/glfw3.h"

namespace Hazel {
	class WindowsWindow: public Window
	{
	public:
		WindowsWindow(const WindowProps& props); // 看样子是会调用父类的构造函数？不，只是作为.h文件的声明
		virtual ~WindowsWindow() {}

		void OnUpdate() override; // 会更新 glfw，缓冲区会轮询输入事件，应该按帧运行，从 Application 中调用
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		// 设置 Application 的回调函数
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		void SetVSync(bool sync) override { m_Data.VSync = sync; }
		bool IsVSync() const override { return m_Data.VSync; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown() {}
	private:
		GLFWwindow* m_Window;
		struct WindowData { // 这个不会和父类的 WindowsProps 重复吗？用于传递给glfw
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};

}

