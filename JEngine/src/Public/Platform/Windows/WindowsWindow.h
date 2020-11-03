#pragma once

#include "Core/Window.h"

#include "Renderer/RenderingContext.h"
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
		virtual void Init(const WindowProperty& windowProperty) override;

		virtual void ShutDown() override;
	private:
		GLFWwindow* m_Window;
		RenderingContext* m_RenderContext;

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
