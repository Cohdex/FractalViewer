#pragma once

#include "FractalViewer/Core/Window.h"

#include <memory>

namespace fv
{
	class FractalViewerApp
	{
	private:
		std::unique_ptr<Window> m_window;

	public:
		FractalViewerApp();

		void run();
	};
}
