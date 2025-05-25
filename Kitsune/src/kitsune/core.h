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