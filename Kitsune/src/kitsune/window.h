#pragma once

#include "kitsune_pch.h"
#include "core/core.h"
#include "kitsune/event/event.h"

namespace kitsune
{
	//window properties
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		//constructor
		WindowProps(const std::string& title = "Kitsune Engine",
			unsigned int width = 1280,
			unsigned int height = 720) :title(title), width(width), height(height) {};
	};

	//window abstraction layer
	class KITSUNE_API Window
	{
	public:
		using EventCallback = Function<void(Event&)>;
		virtual ~Window() {}

		virtual void on_update() = 0;
		virtual unsigned int get_width() const = 0;
		virtual unsigned int get_height() const = 0;

		virtual void set_event_callback(const EventCallback& callback) = 0;
		virtual void vsync(bool enabled) = 0;
		virtual bool vsync() const = 0;

		virtual void* get_native_window() const = 0;

		static Window* create(const WindowProps& props = WindowProps());
	};
}