#include "JE_PCH.h"
#include "Layer/LayerStack.h"

namespace JEngine
{

	LayerStack::LayerStack()
	{
		m_LayerInsertIt = m_LayerStack.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_LayerStack)
			delete layer;
	}
	
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsertIt = m_LayerStack.emplace(m_LayerInsertIt, layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (it != m_LayerStack.end())
		{
			m_LayerStack.erase(it);
			m_LayerInsertIt--;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_LayerStack.emplace_back(overlay);
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), overlay);
		if (it != m_LayerStack.end())
			m_LayerStack.erase(it);
	}

}