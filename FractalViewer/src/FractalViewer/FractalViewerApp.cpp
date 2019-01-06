#include "pch.h"
#include "FractalViewerApp.h"

#include <GL/glew.h>

namespace fv
{
	FractalViewerApp::FractalViewerApp()
	{
		m_window = std::make_unique<Window>(1920, 1080);
		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
		m_window->setMouseCallback(std::bind(&FractalViewerApp::mousePosHandler, this, std::placeholders::_1, std::placeholders::_2));
		m_window->setScrollCallback(std::bind(&FractalViewerApp::scrollHandler, this, std::placeholders::_1));

		/*std::shared_ptr<ShaderStage> geometryShader = std::make_shared<ShaderStage>(R"(
			#version 430 core
			#line 16

			layout(points) in;
			layout(triangle_strip, max_vertices = 3) out;

			out vec2 uv;

			void main()
			{
				gl_Position = vec4(-1.0, 3.0, 0.0, 1.0);
				uv = vec2(0.0, 2.0);
				EmitVertex();

				gl_Position = vec4(-1.0, -1.0, 0.0, 1.0);
				uv = vec2(0.0, 0.0);
				EmitVertex();

				gl_Position = vec4(3.0, -1.0, 0.0, 1.0);
				uv = vec2(2.0, 0.0);
				EmitVertex();

				EndPrimitive();
			})",
			EShaderType::Geometry);*/
		std::shared_ptr<ShaderStage> vertexShader = std::make_shared<ShaderStage>(R"(
			#version 430 core
			#line 42

			out vec2 uv;

			void main()
			{
				float x = -1.0 + float((gl_VertexID & 1) << 2);
				float y = -1.0 + float((gl_VertexID & 2) << 1);
				gl_Position = vec4(x, y, 0.0, 1.0);
				uv = vec2(x, y) * 0.5 + 0.5;
			})",
			EShaderType::Vertex);
		std::shared_ptr<ShaderStage> fragmentShader = std::make_shared<ShaderStage>(R"(
			#version 430 core
			#line 56

			#define PI 3.1415926535897932384626433832795

			in vec2 uv;

			out vec4 fragColor;

			uniform vec2 lowerLeft;
			uniform vec2 upperRight;

			void main()
			{
				vec2 c = mix(lowerLeft, upperRight, uv);

				float zRe = c.x;
				float zIm = c.y;

				int n;
				const int max = 1 << 14;
				for (n = 0; n < max; n++)
				{
					float zRe2 = zRe * zRe;
					float zIm2 = zIm * zIm;
					if ((zRe2 + zIm2) > (2 * 2))
					{
						break;
					}
					zIm = 2 * zRe * zIm + c.y;
					zRe = zRe2 - zIm2 + c.x;
				}

				float i = n / (max - 1.0);
				float r = smoothstep(0.0, 1.0, i);
				float g = 1.0 - exp(-i * 5.0);
				float b = sin(i * PI);
				//b = r * 0.7;
				fragColor = vec4(vec3(r, g, b) * (1.0 - n / max), 1.0);
			})",
			EShaderType::Fragment);
		m_shader = std::make_unique<ShaderProgram>(std::vector<std::shared_ptr<ShaderStage>>{ /*geometryShader,*/ vertexShader, fragmentShader });
	}

	void FractalViewerApp::mousePosHandler(double xPos, double yPos)
	{
		double deltaX = (xPos - m_lastMouseX) / m_window->getWidth();
		double deltaY = (yPos - m_lastMouseY) / m_window->getHeight();
		m_lastMouseX = xPos;
		m_lastMouseY = yPos;
		if (m_window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			m_xPos -= deltaX / m_zoom * 2;
			m_yPos += deltaY / m_zoom * 2;
		}
	}

	void FractalViewerApp::scrollHandler(double scroll)
	{
		m_zoom *= glm::pow(1.1, scroll);
	}

	void FractalViewerApp::run()
	{
		//xPos = -0.7431533999637661f; yPos = -0.1394057861346605f; zoom = 1779.803945297549f;

		GLuint vao;
		glCreateVertexArrays(1, &vao);
		while (!m_window->isCloseRequested())
		{
			double reWidth = 3.0f;
			double minRe = (-reWidth / 2.0f - 0.5f) / m_zoom + m_xPos;
			double maxRe = (reWidth / 2.0f - 0.5f) / m_zoom + m_xPos;
			double imHeight = (maxRe - minRe) * ((float)m_window->getHeight() / m_window->getWidth());
			double minIm = -imHeight / 2 + m_yPos;
			double maxIm = imHeight / 2 + m_yPos;
			m_shader->use();
			m_shader->setUniform("lowerLeft", glm::vec2((float)minRe, (float)minIm));
			m_shader->setUniform("upperRight", glm::vec2((float)maxRe, (float)maxIm));

			GL_CALL(glClearColor(0.3f, 0.5f, 0.8f, 1.0f));
			GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
			m_shader->use();
			glBindVertexArray(vao);
			GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
			m_window->update();
		}
	}
}

int main(void)
{
	std::unique_ptr<fv::FractalViewerApp> app = std::make_unique<fv::FractalViewerApp>();
	app->run();

	return 0;
}
