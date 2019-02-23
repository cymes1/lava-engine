#include "window.h"

namespace LavaEngine { namespace Graphics {

	Window::Window(int width, int height, const char* title)
		: m_width(width), m_height(height)
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	GLFWwindow* Window::handle()
	{
		return m_window;
	}
}}
