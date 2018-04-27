#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include "../utils/log.h"

namespace LavaEngine { namespace Graphics {

	class Window
	{
	private:
		int m_width;
		int m_height;
		GLFWwindow* m_window;

	public:
		Window(int width, int height, const char* title);
		~Window();

		GLFWwindow* handler();
	};
}}

#endif
