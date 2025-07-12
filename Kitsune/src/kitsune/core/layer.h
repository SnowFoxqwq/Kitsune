#pragma once

#include "kitsune/core/core.h"
#include "kitsune/event/event.h"

namespace kitsune
{
	class KITSUNE_API Layer
	{
	public:
		Layer(const std::string& name = "layer");
		virtual ~Layer();

		virtual void on_attach() {}
		virtual void on_detach() {}
		virtual void on_update() {}
		virtual void on_event(Event& event) {}

		const std::string& get_name() const { return _debug_name; }

	private:
		std::string _debug_name;
	};
}