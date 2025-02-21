#pragma once
#include "Events/Event.h"

#include "Core/TimeStep.h"

namespace Hazel {
	class HAZEL_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnAttach() {} // 应用层添加执行
		virtual void OnDetach() {} // 应用层分离此层执行 
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnImGuiRender() {} // 每层都可以拥有自己的一个或多个 ImGui 窗口
		virtual void OnEvent(Event& e) {} 
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
