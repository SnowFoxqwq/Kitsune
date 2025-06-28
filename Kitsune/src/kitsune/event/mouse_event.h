#pragma once

#include "kitsune/event/event.h"
#include "kitsune/core/mouse_code.h"

namespace kitsune
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y)
			: _mouse_x(x), _mouse_y(y) {
		}

		float get_x() const { return _mouse_x; }
		float get_y() const { return _mouse_y; }

		std::string message() const override
		{
			return "<Mouse Moved Event>: (" + std::to_string(_mouse_x) + ", " + std::to_string(_mouse_y) + ")";
		}

		EVENT_CLASS_TYPE(MOUSE_MOVED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)
	private:
		float _mouse_x, _mouse_y;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: _x_offset(xOffset), _y_offset(yOffset) {
		}

		float get_x_offset() const { return _x_offset; }
		float get_y_offset() const { return _y_offset; }

		std::string message() const override
		{
			return "<Mouse Scrolled Event>: (" + std::to_string(get_x_offset()) + ", " + std::to_string(get_y_offset()) + ")";
		}

		EVENT_CLASS_TYPE(MOUSE_SCROLLED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)
	private:
		float _x_offset, _y_offset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseCode get_mouse_button() const { return _button; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE_BUTTON)
	protected:
		MouseButtonEvent(const MouseCode button)
			: _button(button) {
		}

		MouseCode _button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent(button) {
		}

		std::string message() const override
		{

			return "<Mouse Button Pressed Event>: " + std::to_string(_button);
		}

		EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button) {
		}

		std::string message() const override
		{
			return "<Mouse Button Released Event>: " + std::to_string(_button);
		}

		EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED)
	};
}