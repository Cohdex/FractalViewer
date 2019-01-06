#pragma once

#include "FractalViewer/Core/Window.h"
#include "FractalViewer/Core/Shader.h"

#include <memory>

namespace fv
{
	class FractalViewerApp
	{
	private:
		std::unique_ptr<Window> m_window;
		std::unique_ptr<ShaderProgram> m_shader;

		double m_xPos = 0.0;
		double m_yPos = 0.0;
		double m_zoom = 1.0;

		double m_lastMouseX;
		double m_lastMouseY;
		void mousePosHandler(double xPos, double yPos);
		void scrollHandler(double scroll);

	public:
		FractalViewerApp();

		void run();
	};
}
