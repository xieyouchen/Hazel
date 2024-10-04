#pragma once
#include "Layer.h"

namespace Hazel {
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer); // vector 末尾添加一个覆盖层
		void PopLayer(Layer* layer); // 弹出指定层
		void PopOverlay(Layer* layer);
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}


