#include "kitsune_pch.h"
#include "event.h"

namespace kitsune
{
	static std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.message();
	}
}

//The definition had been moved to “application.h”
//In this way, the function can work

//#include <spdlog/fmt/ostr.h>
////add support for event output in spdlog, but actually this doesn't work & nobody knows y.
//template<typename T> 
//struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<kitsune::Event, T>, char>> : fmt::formatter<std::string>
//{
//	auto format(const T& event, format_context& ctx) const -> decltype(ctx.out())
//	{
//		//return fmt::format_to(ctx.out(), "{}", event.message());
//		return fmt::formatter<std::string>::format(event.message(), ctx);
//	}
//};