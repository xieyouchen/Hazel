#include "hzpch.h"

#include "Application.h"
#include "Log.h"
#include "GLFW/glfw3.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Hazel::Application::Application()
	{
		// 创建了一个窗口
		m_Window = std::unique_ptr<Window>(Window::Create());
		
		// 设置窗口事件的回调函数
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Hazel::Application::~Application()
	{
	}	

	void Application::OnEvent(Event& e) 
	{
		// 通过事件调度器判断是否为窗口关闭事件
		EventDispatcher dispatcher(e);
		dispatcher.Dispathcer<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_INFO("{0}", e);
	}

	void Hazel::Application::Run()
	{
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
	// 窗口关闭的回调函数
	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}

