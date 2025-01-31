#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"


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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;	

		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;

		unsigned int m_VertexBuffer;
		unsigned int m_VertexArray;
		unsigned int m_IndexBuffer;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT, e.g. Sandbox
	Application* CreateApplication();
}

