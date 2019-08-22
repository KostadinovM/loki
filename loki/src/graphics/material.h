#pragma once
#include "shader.h"
#include <string>
#include <glm/glm.hpp>
#include <map>

namespace Loki
{
	struct UniformValue
	{
		union
		{
			bool Bool;
			int Int;
			float Float;

			glm::vec2 Vec2;
			glm::vec3 Vec3;
			glm::vec4 Vec4;
			glm::mat2 Mat2;
			glm::mat3 Mat3;
			glm::mat4 Mat4;
		};
	};

	class Material
	{
		private:
			Shader* shader;
			std::map<std::string, UniformValue> uniforms;

		public:
			Material();
			Material(Shader* shader);
			Shader* getShader();
			void setShader(Shader* shader);
			void setBool(std::string name, bool value);
			void setInt(std::string name, int value);
			void setFloat(std::string name, float value);
			void setVector(std::string name, glm::vec2 value);
			void setVector(std::string name, glm::vec3 value);
			void setVector(std::string name, glm::vec4 value);
			void setMatrix(std::string name, glm::mat2 value);
			void setMatrix(std::string name, glm::mat3 value);
			void setMatrix(std::string name, glm::mat4 value);
			std::map<std::string, UniformValue>* getUniforms();
	};
}