#pragma once
#include "Input.h"

namespace JEngine
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyDownImpl(int keycode) override;
		virtual bool IsMouseButtonDownImpl(int mouseButton) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}