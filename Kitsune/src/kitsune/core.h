#pragma once

#ifdef KITSUNE_PLATFORM_WINDOWS
	#ifdef KITSUNE_BUILD_DLL
		#define KITSUNE_API __declspec(dllexport)
	#else
		#define KITSUNE_API __declspec(dllimport)
	#endif // KITSUNE_BUILD_DLL
#else
	#error KITSUNE ONLY SUPPORT WINDOWS NOW!
#endif //KITSUNE_PLATFORM_WINDOWS

#ifdef KITSUNE_DEBUG
	#if defined(KITSUNE_PLATFORM_WINDOWS)
		#define KITSUNE_DEBUGBREAK() __debugbreak()
	#elif defined(KITSUNE_PLATFORM_LINUX)
		#include <signal.h>
		#define KITSUNE_DEBUGBREAK() raise(SIGTRAP)
#else
	#error "Platform doesn't support debugbreak yet!"
#endif
	#define KITSUNE_ENABLE_ASSERTS
#else
	#define KITSUNE_DEBUGBREAK()
#endif

#ifdef KITSUNE_ENABLE_ASSERTS
	#define KITSUNE_ASSERT(FLAG,...) {if(!(FLAG)){KITSUNE_ERROR("Assertion Failed: {0}",__VA_ARGS__);KITSUNE_DEBUGBREAK();}}
	#define KITSUNE_CORE_ASSERT(FLAG,...) {if(!(FLAG)){KITSUNE_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__);KITSUNE_DEBUGBREAK();}}
#else
	#define KITSUNE_ASSERT(FLAG,...)
	#define KITSUNE_CORE_ASSERT(FLAG,...)
#endif

//convert x to bits
#define BIT(x) (1<<x)