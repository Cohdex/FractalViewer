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

	public:
		FractalViewerApp();

		void run();
	};
}
