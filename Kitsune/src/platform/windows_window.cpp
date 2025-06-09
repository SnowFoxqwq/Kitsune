#include "kitsune_pch.h"
#include "windows_window.h"
#include "kitsune/console.h"

namespace kitsune
{

	static bool is_glfw_initialized = false;

	Window* Window::create(const WindowProps& props)
	{
#ifdef KITSUNE_PLATFORM_WINDOWS
		return new WindowsWindow(props);
#endif
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		_init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::on_update()
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
	}

	void WindowsWindow::vsync(bool enabled)
	{
		_data.vsync = enabled;
		if (enabled)
		{
			glfwSwapInterval(1);
			return;
		}
		glfwSwapInterval(0);
	}

	bool WindowsWindow::vsync() const
	{
		return _data.vsync;
	}

	void WindowsWindow::_init(const WindowProps& props)
	{
		_data.title = props.title;
		_data.height = props.height;
		_data.width = props.width;

		KITSUNE_CORE_INFO("window [{0}] is created with size ({1}, {2})", props.title, props.width, props.height);

		if (!is_glfw_initialized)
		{
			int res = glfwInit();
			KITSUNE_ASSERT(res == GLFW_TRUE, "Failed to initialize glfw");
			is_glfw_initialized = true;
		}

		_window = glfwCreateWindow(_data.width, _data.height, _data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(_window);
		glfwSetWindowUserPointer(_window, &_data);
		
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(_window);
	}
}