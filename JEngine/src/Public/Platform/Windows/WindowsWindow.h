#pragma once

#include "Window.h"
#include "GLFW/glfw3.h"

namespace JEngine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperty& windowProperty);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		inline virtual unsigned int GetWindowWidth() const override { return m_WindowData.Width; };
		inline virtual unsigned int GetWindowHeight() const override { return m_WindowData.Height; };

		inline virtual void SetEventCallback(const EventCallbackFunc& callback) override { m_WindowData.EventCallback = callback; };
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; };

	private:
		virtual void Init(const WindowProperty& windowProperty);
		virtual void ShutDown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFunc EventCallback;
		};

		WindowData m_WindowData;
	};
}
