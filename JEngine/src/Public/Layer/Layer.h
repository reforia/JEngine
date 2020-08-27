#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace JEngine
{
	class JE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& e) {};
		virtual void OnImguiRender() {};

		inline std::string& GetName() { return m_DebugName; };
	private:
		std::string m_DebugName;
	};
}