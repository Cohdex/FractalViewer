#include "pch.h"
#include "FractalViewer/Core/Window.h"

namespace fv
{
	Window::Window(int width, int height)
	{
		if (!glfwInit()) {
			std::cout << "Could not inialize GLFW!" << std::endl;
			throw 1;
		}

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		m_window = glfwCreateWindow(width, height, "Fractal Viwer", nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
}
