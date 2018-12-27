#include "pch.h"
#include "FractalViewerApp.h"

#include <GL/glew.h>

namespace fv
{
	FractalViewerApp::FractalViewerApp()
	{
		m_window = std::make_unique<Window>(1920, 1080);
	}

	void FractalViewerApp::run()
	{
		while (true)
		{
			m_window->update();
			glClearColor(0.3f, 0.5f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
}

int main(void)
{
	auto app = std::make_unique<fv::FractalViewerApp>();
	app->run();

	return 0;
}
