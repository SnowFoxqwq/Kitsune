#include "kitsune_pch.h"
#include "application.h"
#include "console.h"
#include "event/application_event.h"

#include <spdlog/fmt/ostr.h>
namespace fmt
{
	template<typename T>
	struct formatter<T, std::enable_if_t<std::is_base_of_v<kitsune::Event, T>, char>> {
		constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
			return ctx.begin();
		}

		template<typename FormatContext>
		auto format(const T& event, FormatContext& ctx) const -> decltype(ctx.out()) {
			return fmt::format_to(ctx.out(), "{}", event.message());
		}
	};
}

#include <GLFW/glfw3.h>

namespace kitsune
{
#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)
	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::create());
		_window->set_event_callback(BIND_EVENT_FUNCTION(Application::on_event));

		unsigned int id;
		glGenBuffers(1, &id);
		KITSUNE_CORE_INFO(id);

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

			for (auto layer : _layer_stack)
			{
				layer->on_update();
			}

			_window->on_update();

		}
	}
	void Application::on_event(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::on_window_close));
		KITSUNE_CORE_TRACE("Application: Event Received {0}", event);

		for (auto it = _layer_stack.end(); it != _layer_stack.begin();)
		{
			(*--it)->on_event(event);
			if (event.handled)
			{
				break;
			}
		}

	}

	void Application::push_layer(Layer* layer)
	{
		_layer_stack.push_layer(layer);
	}

	void Application::push_overlay(Layer* overlay)
	{
		_layer_stack.push_overlay(overlay);
	}

	bool Application::on_window_close(WindowCloseEvent& event)
	{
		_is_running = false;
		return true;
	}
}