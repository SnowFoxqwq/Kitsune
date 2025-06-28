#include "kitsune_pch.h"
#include "layer_stack.h"

namespace kitsune
{
	LayerStack::LayerStack()
	{
		_layer_insert = _layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (auto layer : _layers)
		{
			delete layer;
		}
	}

	void LayerStack::push_layer(Layer* layer)
	{
		_layer_insert = _layers.emplace(_layer_insert, layer);
	}

	void LayerStack::push_overlay(Layer* overlay)
	{
		_layers.emplace_back(overlay);
	}

	void LayerStack::pop_layer(Layer* layer)
	{  
		auto it = std::find(_layers.begin(), _layers.end(), layer);
		if (it != _layers.end())
		{
			_layers.erase(it);
			_layer_insert--;
		}
	}

	void LayerStack::pop_overlay(Layer* overlay)
	{
		auto it = std::find(_layers.begin(), _layers.end(), overlay);
		if (it != _layers.end())
		{
			_layers.erase(it);
		}
	}
}