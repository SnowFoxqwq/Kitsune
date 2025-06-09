#pragma once

#ifdef KITSUNE_PLATFORM_WINDOWS

extern kitsune::Application* kitsune::create_application();

int main(int argc, char** argv)
{
	system("chcp 65001");
	system("cls");

	kitsune::Console::init();
	KITSUNE_INFO("welcome to kitsune!");
	KITSUNE_WARN("❤️");

	auto app = kitsune::create_application();
	app->run();
	delete app;
	return 0;
}
#endif