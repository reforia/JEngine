#pragma once

#include "Core.h"

namespace JEngine
{
	class JE_API Input
	{
	public:
		inline static bool IsKeyDown(int keycode) { return s_Instance->IsKeyDownImpl(keycode); };
		inline static bool IsMouseButtonDown(int mouseButton) { return s_Instance->IsMouseButtonDownImpl(mouseButton); };
		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); };
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); };
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); };
		
	protected:
		virtual bool IsKeyDownImpl(int keycode) = 0;
		virtual bool IsMouseButtonDownImpl(int mouseButton) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}