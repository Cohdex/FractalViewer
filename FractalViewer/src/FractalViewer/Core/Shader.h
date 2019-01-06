#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace fv
{
	enum class EShaderType
	{
		Geometry, Vertex, Fragment
	};

	class ShaderStage
	{
		friend class ShaderProgram;

	private:
		EShaderType m_shaderType;
		GLuint m_shader;

	public:
		ShaderStage(const std::string& source, EShaderType shaderType);
		~ShaderStage();
	};

	class ShaderProgram
	{
	private:
		GLuint m_program;

	public:
		ShaderProgram(const std::vector<std::shared_ptr<ShaderStage>>& shaderStages);
		~ShaderProgram();

		void use() const;

		void setUniform(const std::string& name, const glm::vec2& value);
	};
}
