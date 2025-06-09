#pragma once

#include "core.h"
#include "window.h"

namespace kitsune
{
	class KITSUNE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	private:
		std::unique_ptr<Window> _window;
		bool _is_running = true;
	};

	Application* create_application();
}