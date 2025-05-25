#pragma once

#include <memory>
#include "core.h"
#include <spdlog/spdlog.h>

namespace kitsune
{
	class KITSUNE_API Console
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return _core_logger; }
		inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return _client_logger; }

	private:
		static std::shared_ptr<spdlog::logger> _core_logger;
		static std::shared_ptr<spdlog::logger> _client_logger;
	};
}

// core logging marcos
#define KITSUNE_CORE_TRACE(...)   ::kitsune::Console::get_core_logger()->trace(__VA_ARGS__)
#define KITSUNE_CORE_INFO(...)    ::kitsune::Console::get_core_logger()->info(__VA_ARGS__)
#define KITSUNE_CORE_WARN(...)    ::kitsune::Console::get_core_logger()->warn(__VA_ARGS__)
#define KITSUNE_CORE_ERROR(...)   ::kitsune::Console::get_core_logger()->error(__VA_ARGS__)
#define KITSUNE_CORE_FATAL(...)   ::kitsune::Console::get_core_logger()->fatal(__VA_ARGS__)
								  
// client logging marcos		 	  
#define KITSUNE_TRACE(...)        ::kitsune::Console::get_client_logger()->trace(__VA_ARGS__)
#define KITSUNE_INFO(...)         ::kitsune::Console::get_client_logger()->info(__VA_ARGS__)
#define KITSUNE_WARN(...)         ::kitsune::Console::get_client_logger()->warn(__VA_ARGS__)
#define KITSUNE_ERROR(...)        ::kitsune::Console::get_client_logger()->error(__VA_ARGS__)
#define KITSUNE_FATAL(...)        ::kitsune::Console::get_client_logger()->fatal(__VA_ARGS__)