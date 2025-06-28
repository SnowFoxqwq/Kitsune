#include<Kitsune.h>

class ExampleLayer :public kitsune::Layer
{
public:
	ExampleLayer() :kitsune::Layer("Example")
	{

	}
	void on_update() override
	{
		KITSUNE_INFO("<ExampleLayer>: on update");
	}
	void on_event(kitsune::Event& event) override
	{
		KITSUNE_INFO("<ExampleLayer>: on update");
	}
};

class Sandbox : public kitsune::Application
{
public:
	Sandbox()
	{
		push_layer(new ExampleLayer);
	}
	~Sandbox()
	{

	}
};

kitsune::Application* kitsune::create_application()
{
	return new Sandbox();
}