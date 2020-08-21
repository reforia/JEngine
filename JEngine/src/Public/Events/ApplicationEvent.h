// ALL APPLICATION EVENTS ARE DEFINED HERE
#pragma once

#include "Event.h"

namespace JEngine
{
	class JE_API WindowResizeEvent : public Event 
	{
	public:
		WindowResizeEvent(int Width, int Height)
			:m_Width(Width), m_Height(Height){}

		inline int GetWindowWidth() const { return m_Width; };
		inline int GetWindowHeight() const { return m_Height; };
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: New Window Size: (" << m_Width << "," << m_Height << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class JE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class JE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class JE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class JE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}