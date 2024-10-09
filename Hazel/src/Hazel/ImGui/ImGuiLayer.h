#pragma once
#include "Hazel/Layer.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

namespace Hazel {
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const std::string& name = "ImGuiLayer");
		~ImGuiLayer();
		void OnAttach(); // 应用层添加执行
		void OnDetach(); // 应用层分离此层执行 
		void OnUpdate();
		void OnEvent(Event& e);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);



	private:
		float m_time = 0.0f;
	};
}


