#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace Loki
{
	class Shader
	{
	private:
		unsigned int id;

	private:		
		std::string readShaderFile(std::string shaderPath);

	public:
		Shader();
		Shader(std::string vertexPath, std::string fragmentPath);
		void load(std::string vertexShader, std::string fragmentShader);
		void use();
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
			
		void setVector(const std::string& name, glm::vec2& vec) const;
		void setVector(const std::string& name, glm::vec3& vec) const;
		void setVector(const std::string& name, glm::vec4& vec) const;

		void setMatrix(const std::string& name, glm::mat2& mat) const;
		void setMatrix(const std::string& name, glm::mat3& mat) const;
		void setMatrix(const std::string& name, glm::mat4& mat) const;

		unsigned int getID();

	};
}