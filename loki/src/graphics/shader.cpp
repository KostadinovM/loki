#include "shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Loki
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

		int status;
		char log[1024];

		glShaderSource(vs, 1, &vShaderCode, NULL);
		glShaderSource(fs, 1, &fShaderCode, NULL);

		glCompileShader(vs);
		glCompileShader(fs);

		glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			glGetShaderInfoLog(vs, 1024, NULL, log);
			std::cout << "Vertex shader compilation error at: " << vertexShader << std::endl;
			std::cout << "Log: " << std::string(log) << std::endl;
		}
		glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			glGetShaderInfoLog(vs, 1024, NULL, log);
			std::cout << "Vertex shader compilation error at: " << vertexShader << std::endl;
			std::cout << "Log: " << std::string(log) << std::endl;
		}

		glAttachShader(id, vs);
		glAttachShader(id, fs);

		glLinkProgram(id);

		glGetProgramiv(id, GL_LINK_STATUS, &status);
		if (!status)
		{
			glGetProgramInfoLog(id, 1024, NULL, log);
			std::cout << "Log: " << std::string(log) << std::endl;
		}

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	void Shader::use()
	{
		glUseProgram(id);
	}

	void Shader::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

	void Shader::setVector(const std::string& name, glm::vec2& vec) const
	{
		glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &vec[0]);
	}

	void Shader::setVector(const std::string& name, glm::vec3& vec) const
	{
		glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &vec[0]);
	}

	void Shader::setVector(const std::string& name, glm::vec4& vec) const
	{
		glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &vec[0]);
	}

	void Shader::setMatrix(const std::string& name, glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setMatrix(const std::string& name, glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setMatrix(const std::string& name, glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	unsigned int Shader::getID()
	{
		return id;
	}

	std::string Shader::readShaderFile(std::string path, std::string includeIndentifier)
	{
		includeIndentifier += ' ';
		static bool isRecursiveCall = false;

		std::string fullSourceCode = "";
		std::ifstream file(path);

		if (!file.is_open())
		{
			std::cerr << "ERROR: could not open the shader at: " << path << "\n" << std::endl;
			return fullSourceCode;
		}

		std::string lineBuffer;
		while (std::getline(file, lineBuffer))
		{
			// Look for the new shader include identifier
			if (lineBuffer.find(includeIndentifier) != lineBuffer.npos)
			{
				// Remove the include identifier, this will cause the path to remain
				lineBuffer.erase(0, includeIndentifier.size());

				// The include path is relative to the current shader file path
				std::string pathOfThisFile;
				getFilePath(path, pathOfThisFile);
				lineBuffer.insert(0, pathOfThisFile);

				// By using recursion, the new include file can be extracted
				// and inserted at this location in the shader source code
				isRecursiveCall = true;
				fullSourceCode += readShaderFile(lineBuffer);

				// Do not add this line to the shader source code, as the include
				// path would generate a compilation issue in the final source code
				continue;
			}

			fullSourceCode += lineBuffer + '\n';
		}

		// Only add the null terminator at the end of the complete file,
		// essentially skipping recursive function calls this way
		if (!isRecursiveCall)
			fullSourceCode += '\0';

		file.close();

		return fullSourceCode;
	}

	void Shader::getFilePath(const std::string& fullPath, std::string& pathWithoutFileName)
	{
		// Remove the file name and store the path to this folder
		size_t found = fullPath.find_last_of("/\\");
		pathWithoutFileName = fullPath.substr(0, found + 1);
	}
}


