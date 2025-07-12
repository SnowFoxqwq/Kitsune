#pragma once

#include <glad/glad.h>

#include "kitsune/core/core.h"
#include "window.h"
#include "kitsune/event/application_event.h"
#include "kitsune/core/layer_stack.h"

namespace kitsune
{
	class KITSUNE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();

		void on_event(Event& event);

		void push_layer(Layer* layer);
		void push_overlay(Layer* overlay);

		static Application& get() { return *_instance; };

		Window& get_window() { return *_window; }

	private:
		bool on_window_close(WindowCloseEvent& event);
	private:
		std::unique_ptr<Window> _window;
		bool _is_running = true;
		LayerStack _layer_stack;

		static Application* _instance;

	};

	Application* create_application();
}