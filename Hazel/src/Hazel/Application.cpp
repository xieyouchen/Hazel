#include "hzpch.h"

#include "Application.h"
#include "Log.h"
//#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Input.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Hazel::Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// 创建了一个窗口
		m_Window = std::unique_ptr<Window>(Window::Create());
		
		// 设置窗口事件的回调函数
		// param: std::function<void(Event&)>
		//m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// 将 ImGuiLayer 放在最后
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
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
		//HZ_ERROR("Application OnEvent");
		// 通过事件调度器判断是否为窗口关闭事件
		EventDispatcher dispatcher(e);
		//dispatcher.Dispathcer<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispathcer<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.m_Handled) {
				break;
			}
		}
		
		//HZ_CORE_INFO("{0}", e); // 开头会带 Hazel，绿色字体
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

			// 从前往后顺序更新层
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			// 从前往后顺序更新层
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}

