#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"


namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;	

		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT, e.g. Sandbox
	Application* CreateApplication();
}

