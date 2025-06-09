#include<Kitsune.h>

class Sandbox : public kitsune::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

kitsune::Application* kitsune::create_application()
{
	return new Sandbox();
}