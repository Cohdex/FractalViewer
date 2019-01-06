#include "pch.h"
#include "Shader.h"

#include <cstdarg>

namespace fv
{
	static GLenum get_shader_type_enum(EShaderType shaderType)
	{
		switch (shaderType)
		{
		case EShaderType::Geometry:
			return GL_GEOMETRY_SHADER;
		case EShaderType::Vertex:
			return GL_VERTEX_SHADER;
		case EShaderType::Fragment:
			return GL_FRAGMENT_SHADER;
		default:
			throw "Unsupported shader type";
		}
	}

	static GLuint compile_shader(const char* source, EShaderType shaderType)
	{
		GL_CALL(GLuint shader = glCreateShader(get_shader_type_enum(shaderType)));
		GL_CALL(glShaderSource(shader, 1, &source, nullptr));
		GL_CALL(glCompileShader(shader));
		GLint success;
		GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
		if (success != GL_TRUE)
		{
			GLint logLength;
			GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength));
			std::vector<GLchar> infoLog(logLength);
			GL_CALL(glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data()));
			GL_CALL(glDeleteShader(shader));
			std::cout << "Could not compile shader: " << infoLog.data() << std::endl;
			throw "Could not compile shader";
		}
		return shader;
	}

	ShaderStage::ShaderStage(const std::string& source, EShaderType shaderType)
		: m_shaderType(shaderType)
	{
		m_shader = compile_shader(source.c_str(), shaderType);
	}

	ShaderStage::~ShaderStage()
	{
		GL_CALL(glDeleteShader(m_shader));
	}

	ShaderProgram::ShaderProgram(const std::vector<std::shared_ptr<ShaderStage>>& shaderStages)
	{
		GL_CALL(m_program = glCreateProgram());
		for (const std::shared_ptr<ShaderStage>& shader : shaderStages)
		{
			GL_CALL(glAttachShader(m_program, shader->m_shader));
		}
		GL_CALL(glLinkProgram(m_program));
		for (const std::shared_ptr<ShaderStage>& shader : shaderStages)
		{
			GL_CALL(glDetachShader(m_program, shader->m_shader));
		}
		GLint success;
		GL_CALL(glGetProgramiv(m_program, GL_LINK_STATUS, &success));
		if (success != GL_TRUE)
		{
			GLint logLength;
			GL_CALL(glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength));
			std::vector<GLchar> infoLog(logLength);
			GL_CALL(glGetProgramInfoLog(m_program, logLength, nullptr, infoLog.data()));
			GL_CALL(glDeleteProgram(m_program));
			std::cout << "Could not link shader: " << infoLog.data() << std::endl;
			throw "Could not link shader";
		}
	}

	ShaderProgram::~ShaderProgram()
	{
		GL_CALL(glDeleteProgram(m_program));
	}

	void ShaderProgram::use() const
	{
		GL_CALL(glUseProgram(m_program));
	}

	void ShaderProgram::setUniform(const std::string& name, const glm::vec2& value)
	{
		GL_CALL(GLint location = glGetUniformLocation(m_program, name.c_str()));
		GL_CALL(glUniform2fv(location, 1, &value[0]));
	}
}
