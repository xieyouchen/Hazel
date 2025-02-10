#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"


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

		std::shared_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<Shader> m_Shader;

		std::shared_ptr<VertexArray> m_SquareVAO;
		std::unique_ptr<Shader> m_BlueShader;
	private:
		static Application* s_Instance;

	};

	// To be defined in CLIENT, e.g. Sandbox
	Application* CreateApplication();
}

