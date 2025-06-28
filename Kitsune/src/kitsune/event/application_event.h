#pragma once

#include "kitsune/core/core.h"
#include "event.h"

namespace kitsune
{
	class KITSUNE_API WindowResizeEvent :public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) :_width(width), _height(height) {}

		unsigned int get_width() const { return _width; }
		unsigned int get_height() const { return _height; }

		std::string message() const override 
		{ 
			return "<Window Resize Event>: ( " + std::to_string(_width) + ", " + std::to_string(_height) + " )";
		}

		EVENT_CLASS_TYPE(WINDOW_RESIZE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)

	private:
		unsigned int _width, _height;
	};

	class KITSUNE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		std::string message() const override
		{
			return "<Window Close Event>";
		}

		EVENT_CLASS_TYPE(WINDOW_CLOSE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

	class KITSUNE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(APPLICATION_TICK)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

	class KITSUNE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(APPLICATION_UPDATE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

	class KITSUNE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(APPLICATION_RENDER)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};
}