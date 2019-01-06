#pragma once

#include <GLFW/glfw3.h>

namespace fv
{
	class Window
	{
	private:
		GLFWwindow* m_window;
		int m_width;
		int m_height;

	public:
		Window(int width, int height);
		~Window();

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }

		void update();

		bool isCloseRequested() const;
	};
}
