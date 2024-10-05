#include "hzpch.h"

#include "Application.h"
#include "Log.h"
//#include "GLFW/glfw3.h"
#include "glad/glad.h"

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

	// ------ Layer
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e) 
	{
		// 通过事件调度器判断是否为窗口关闭事件
		EventDispatcher dispatcher(e);
		dispatcher.Dispathcer<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_INFO("{0}", e);
	}

	// 窗口关闭的回调函数
	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Hazel::Application::Run()
	{
		while (m_Running) {
			// run中使用了opengl函数
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}
}

