#pragma once
#include "Hazel/Layer.h"

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
		float m_time = 0.0f;
	};
}


