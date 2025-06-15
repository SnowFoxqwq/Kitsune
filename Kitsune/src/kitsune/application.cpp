#include "kitsune_pch.h"
#include "application.h"
#include "console.h"
#include "event/application_event.h"

#include <GLFW/glfw3.h>

namespace kitsune
{
#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)
	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::create());
		_window->set_event_callback(BIND_EVENT_FUNCTION(Application::on_event));
	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		while (_is_running)
		{
			glClearColor(0.f, (float)(47.f / 255.f), (float)(167.f / 255.f), 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			_window->on_update();

		}
	}
	void Application::on_event(Event& event)
	{
		KITSUNE_CORE_INFO("Application: Event Received {0}", event);
	}
}