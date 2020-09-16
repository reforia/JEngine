#pragma once

#include "Core.h"
#include "Events/Event.h"

#include "Core/Timestep.h"

namespace JEngine
{
	class JE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(const Timestep& DeltaTime) {};
		virtual void OnEvent(Event& e) {};
		virtual void OnImguiRender() {};

		inline std::string& GetName() { return m_DebugName; };
	private:
		std::string m_DebugName;
	};
}