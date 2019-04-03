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

		Shader::Shader(std::string vertexShader, std::string fragmentShader)
		{
			std::string vShaderCode = readShaderFile(vertexShader);
			std::string fShaderCode = readShaderFile(fragmentShader);
			load(vShaderCode, fShaderCode);
		}

		void Shader::load(std::string vertexShader, std::string fragmentShader)
		{
			unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
			unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

			ID = glCreateProgram();

			const GLchar* vShaderCode = vertexShader.c_str();
			const GLchar* fShaderCode = fragmentShader.c_str();

			glShaderSource(vs, 1, &vShaderCode, NULL);
			glShaderSource(fs, 1, &fShaderCode, NULL);

			glCompileShader(vs);
			glCompileShader(fs);

			glAttachShader(ID, vs);
			glAttachShader(ID, fs);

			glLinkProgram(ID);

			glDeleteShader(vs);
			glDeleteShader(fs);
		}

		void Shader::use()
		{
			glUseProgram(ID);
		}

		void Shader::setBool(std::string name, bool value)
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
		}

		void Shader::setInt(std::string name, int value)
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
		}

		void Shader::setFloat(std::string name, float value)
		{
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
		}

		std::string Shader::readShaderFile(std::string& shaderPath)
		{
			std::ifstream t(shaderPath);
			std::stringstream buffer;
			buffer << t.rdbuf();
			std::string shaderCode = buffer.str();
			return shaderCode;
		}
	}
}


