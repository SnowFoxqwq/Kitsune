#pragma once

#include "kitsune/core/layer.h"

namespace kitsune
{
	class KITSUNE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void on_attach() override;
		void on_detach() override;
		void on_update() override;
		void on_event(Event& event) override;
	private:
		float _time = 0.0f;
	};
}