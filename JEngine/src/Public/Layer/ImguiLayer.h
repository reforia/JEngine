#pragma once

#include "Layer.h"
#include "../Events/ApplicationEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

namespace JEngine
{
	class JE_API ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImguiRender() override;

		void begin();
		void end();
	private:
		float m_Time = 0.0f;
	};
}
