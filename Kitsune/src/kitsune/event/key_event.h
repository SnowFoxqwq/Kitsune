#pragma once

#include "kitsune/event/event.h"
#include "kitsune/core/key_codes.h"

namespace kitsune 
{

	class KeyEvent : public Event
	{
	public:
		KeyCode get_key_code() const { return _key_code; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT)
	protected:
		KeyEvent(const KeyCode keycode)
			: _key_code(keycode) {
		}

		KeyCode _key_code;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
			: KeyEvent(keycode), _is_repeat(isRepeat) {
		}

		bool is_repeat() const { return _is_repeat; }

		std::string message() const override
		{

			return "<Key Pressed Event>: " + _key_code + std::string(" (repeat = ") + std::to_string(_is_repeat) + std::string(")");
		}

		EVENT_CLASS_TYPE(KEY_PRESSED)
	private:
		bool _is_repeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {
		}

		std::string message() const override
		{
			return "<Key Released Event>: " + std::to_string(_key_code);
		}

		EVENT_CLASS_TYPE(KEY_RELEASED)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {
		}

		std::string message() const override
		{
			return "<Key Typed Event>: " + std::to_string(_key_code);
		}

		EVENT_CLASS_TYPE(KEY_TYPED)
	};
}