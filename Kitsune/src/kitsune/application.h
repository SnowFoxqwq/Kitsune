#pragma once

#include"core.h"

namespace kitsune
{
	class KITSUNE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	};

	Application* create_application();
}