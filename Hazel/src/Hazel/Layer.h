#pragma once
#include "Events/Event.h"

namespace Hazel {
	class HAZEL_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnAttach() {} // 应用层添加执行
		virtual void OnDetach() {} // 应用层分离此层执行 
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
