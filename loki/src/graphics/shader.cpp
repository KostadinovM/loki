#include "shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Loki
{
	namespace Graphics
	{

		Shader::Shader()
		{

		}

		Shader::Shader(std::string vertexPath, std::string fragmentPath)
		{
			std::string vShaderCode = readShaderFile(vertexPath);
			std::string fShaderCode = readShaderFile(fragmentPath);
			load(vShaderCode, fShaderCode);
		}

		void Shader::load(std::string vertexShader, std::string fragmentShader)
		{
			unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
			unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

			id = glCreateProgram();

			const GLchar* vShaderCode = vertexShader.c_str();
			const GLchar* fShaderCode = fragmentShader.c_str();

			glShaderSource(vs, 1, &vShaderCode, NULL);
			glShaderSource(fs, 1, &fShaderCode, NULL);

			glCompileShader(vs);
			glCompileShader(fs);

			glAttachShader(id, vs);
			glAttachShader(id, fs);

			glLinkProgram(id);

			glDeleteShader(vs);
			glDeleteShader(fs);
		}

		void Shader::use()
		{
			glUseProgram(id);
		}

		void Shader::setBool(std::string& name, bool value) const
		{
			glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
		}

		void Shader::setInt(const std::string& name, int value) const
		{
			glUniform1i(glGetUniformLocation(id, name.c_str()), value);
		}

		void Shader::setFloat(std::string& name, float value) const
		{
			glUniform1f(glGetUniformLocation(id, name.c_str()), value);
		}

		std::string Shader::readShaderFile(std::string shaderPath)
		{
			std::ifstream t(shaderPath);
			std::stringstream buffer;
			buffer << t.rdbuf();
			std::string& shaderCode = buffer.str();
			return shaderCode;
		}
	}
}


