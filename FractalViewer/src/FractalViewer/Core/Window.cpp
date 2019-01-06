#include "pch.h"
#include "FractalViewer/Core/Window.h"

static void GLAPIENTRY opengl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

namespace fv
{
	Window::Window(int width, int height)
	{
		if (!glfwInit()) {
			std::cout << "Could not inialize GLFW!" << std::endl;
			throw "Could not inialize GLFW!";
		}

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_window = glfwCreateWindow(width, height, "Fractal Viwer", nullptr, nullptr);
		if (m_window == nullptr) {
			std::cout << "Could not create window!" << std::endl;
			glfwTerminate();
			throw "Could not create window!";
		}
		glfwGetWindowSize(m_window, &m_width, &m_height);
		glfwMakeContextCurrent(m_window);

		glewExperimental = GL_TRUE;
		if (GLenum err = glewInit() != GLEW_OK) {
			std::cout << "Could not initialize GLEW: " << glewGetErrorString(err) << std::endl;
			glfwTerminate();
			throw "Could not initialize GLEW!";
		}

		glEnable(GL_DEBUG_OUTPUT);
		//glDebugMessageCallback(opengl_error_callback, nullptr);

		GL_CALL(glViewport(0, 0, m_width, m_height));
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

	bool Window::isCloseRequested() const
	{
		return glfwWindowShouldClose(m_window);
	}
}
