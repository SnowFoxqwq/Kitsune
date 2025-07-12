#include "kitsune_pch.h"

#include "windows_window.h"
#include "kitsune/console.h"

#include "kitsune/event/application_event.h"
#include "kitsune/event/key_event.h"
#include "kitsune/event/mouse_event.h"

namespace kitsune
{

	static bool is_glfw_initialized = false;

	static void glfw_error_callback(int error, const char* msg)
	{
		KITSUNE_CORE_ERROR("glfw error: {0},message: {1}", error, msg);
	}

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
		_shutdown();
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
			KITSUNE_CORE_ASSERT(res == GLFW_TRUE, "Failed to initialize glfw");
			is_glfw_initialized = true;

			glfwSetErrorCallback(glfw_error_callback);
		}

		_window = glfwCreateWindow(_data.width, _data.height, _data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(_window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KITSUNE_CORE_ASSERT(status, "Failed to initialize glad");

		glfwSetWindowUserPointer(_window, &_data);

		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.callback(event);
			});

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				WindowCloseEvent event;
				data.callback(event);
			});

		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scan_code, int action, int mods)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, false);
						data.callback(event);
						break;
					}

					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.callback(event);
						break;
					}

					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, true);
						data.callback(event);
						break;
					}

					default:
						break;
					}

			});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.callback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.callback(event);
						break;
					}
					default:
						break;
				}
			});

		glfwSetScrollCallback(_window, [](GLFWwindow* window, double x_offset, double y_offset)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				MouseScrolledEvent event((float)x_offset, (float)(y_offset));
				data.callback(event);
			});

		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x_pos, double y_pos)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				MouseMovedEvent event((float)(x_pos), (float)(y_pos));
				data.callback(event);
			});
		
	}

	void WindowsWindow::_shutdown()
	{
		glfwDestroyWindow(_window);
	}
}