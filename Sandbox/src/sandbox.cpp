#include<Kitsune.h>

class Sandbox : public kitsune::Application
{
public:
	Sandbox()
	{
		push_overlay(new kitsune::ImGuiLayer);
	}
	~Sandbox()
	{

	}
};

kitsune::Application* kitsune::create_application()
{
	return new Sandbox();
}