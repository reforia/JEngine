#pragma once

#include "Core/Core.h"
#include "Layer/Layer.h"

#include <vector>

namespace JEngine 
{
	class JE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		// Issue here is, there's no guard code to evaluate if a layer is an overlay or not.
		// It would be better if we could derive layer and overlay from there base class
		// However, by store them into a single vector would cause Object Slicing.
		// Dubly Linked List (list<>) can solve this specific problem
		// Currently, since there isn't much insert nor delete action, a vector<Layer*> is enough
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_LayerStack.begin(); };
		std::vector<Layer*>::iterator end() { return m_LayerStack.end(); };

	private:
		std::vector<Layer*> m_LayerStack;
		unsigned int m_LayerInsertItIndex = 0;
	};
}