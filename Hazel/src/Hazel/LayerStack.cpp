#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {
	LayerStack::LayerStack() {
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		// 在指定位置之前插入一个新层，返回插入新层的位置 (那位置似乎没变？)
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		layer->OnAttach();
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* layer) {
		m_Layers.emplace_back(layer);
		layer->OnAttach();
		m_LayerInsertIndex++;
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsertIndex--; // 指向 Begin？
		}
	}

	void LayerStack::PopOverlay(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}
}
