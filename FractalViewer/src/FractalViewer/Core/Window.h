#pragma once

#include <GLFW/glfw3.h>

#include <functional>

namespace fv
{
	using MouseCallback = std::function<void(double xPos, double yPos)>;
	using ScrollCallback = std::function<void(double verticalScroll)>;

	class Window
	{
	private:
		GLFWwindow* m_window;
		int m_width;
		int m_height;
		MouseCallback m_mouseCallback;
		ScrollCallback m_scrollCallback;

	public:
		Window(int width, int height);
		~Window();

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }

		void update();

		bool isCloseRequested() const;

		static void glfwMousePosCallback(GLFWwindow* window, double xPos, double yPos);
		void setMouseCallback(MouseCallback callback);

		static void glfwScrollCallback(GLFWwindow* window, double xScroll, double yScroll);
		void setScrollCallback(ScrollCallback callback);

		bool isMouseButtonPressed(int button);
	};
}
