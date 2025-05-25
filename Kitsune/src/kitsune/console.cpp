#include "Console.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace kitsune
{
	std::shared_ptr<spdlog::logger> Console::_core_logger;
	std::shared_ptr<spdlog::logger> Console::_client_logger;

	void Console::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		_core_logger = spdlog::stdout_color_mt("Kitsune");
		_core_logger->set_level(spdlog::level::trace);

		_client_logger = spdlog::stdout_color_mt("Client");
		_core_logger->set_level(spdlog::level::trace);

	}
}