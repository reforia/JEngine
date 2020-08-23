// ALL KEY EVENTS ARE DEFINED HERE
#pragma once

#include "Event.h"

namespace JEngine 
{
	class JE_API KeyEvent : public Event 
	{
	public:
		inline int GetKeyCode() { return m_KeyCode; };

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode){}

		int m_KeyCode;
	};

	class JE_API KeyPressedEvent : public KeyEvent 
	{
	public:
		KeyPressedEvent(int KeyCode, int RepeatCount)
			:KeyEvent(KeyCode),m_RepeatCount(RepeatCount){}

		inline int GetRepeatCount() { return m_RepeatCount; };

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << " Repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class JE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int KeyCode)
			:KeyEvent(KeyCode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
