#include "JE_PCH.h"
#include "Platform/Windows/WindowsInput.h"

#include "Application.h"
#include "GLFW/glfw3.h"

namespace JEngine
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyDownImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto status = glfwGetKey(window, keycode);
		return status == GLFW_PRESS || status == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonDownImpl(int mouseButton)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto status = glfwGetMouseButton(window, mouseButton);
		return status == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}

}