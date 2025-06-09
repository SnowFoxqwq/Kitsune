#pragma once

#include "kitsune/window.h"
#include <GLFW/glfw3.h>

namespace kitsune
{
	class KITSUNE_API WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void on_update() override;

		unsigned int get_width() const override { return _data.width; }
		unsigned int get_height() const override { return _data.height; }

		void set_event_callback(const EventCallback& callback) override { _data.callback = callback; }
		void vsync(bool enabled) override;
		bool vsync() const override;
	private:

		virtual void _init(const WindowProps& props);
		virtual void shutdown();

	private:
		GLFWwindow* _window = nullptr;
		struct WindowData
		{
			std::string title = "KITSUNE WINDOW";
			unsigned int height = 640, width = 480;
			bool vsync = true;
			EventCallback callback;
		};
		WindowData _data;
	};
}