#pragma once

#include "JE_PCH.h"

#include "Core.h"
#include "Events/Event.h"

namespace JEngine 
{
	struct WindowProperty
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		// Constructor
		WindowProperty(std::string title="JEngine Editor",
						unsigned int width=1280, 
						unsigned int height=720)
			:Title(title),Width(width),Height(height)
		{}
	};

	class JE_API Window 
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWindowWidth() const = 0;
		virtual unsigned int GetWindowHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void Init(const WindowProperty& windowProperty) = 0;
		virtual void ShutDown() = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* CreateJEWindow(const WindowProperty& property = WindowProperty());
	};
}
