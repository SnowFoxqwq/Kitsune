#include "kitsune_pch.h"
#include "application.h"
#include "console.h"
#include "event/application_event.h"

#include <GLFW/glfw3.h>

namespace kitsune
{
	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::create());
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
}