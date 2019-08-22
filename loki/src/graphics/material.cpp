#include "material.h"

namespace Loki
{
	Material::Material()
	{

	}

	Material::Material(Shader* shader) :
		shader(shader)
	{

	}

	Shader* Material::getShader()
	{
		return this->shader;
	}

	void Material::setShader(Shader* shader)
	{
		this->shader = shader;
	}

	void Material::setBool(std::string name, bool value)
	{
		uniforms[name].Bool = value;
	}

	void Material::setInt(std::string name, int value)
	{
		uniforms[name].Int = value;
	}

	void Material::setFloat(std::string name, float value)
	{
		uniforms[name].Float = value;
	}

	void Material::setVector(std::string name, glm::vec2 value)
	{
		uniforms[name].Vec2 = value;
	}

	void Material::setVector(std::string name, glm::vec3 value)
	{
		uniforms[name].Vec3 = value;
	}

	void Material::setVector(std::string name, glm::vec4 value)
	{
		uniforms[name].Vec4 = value;
	}

	void Material::setMatrix(std::string name, glm::mat2 value)
	{
		uniforms[name].Mat2 = value;
	}

	void Material::setMatrix(std::string name, glm::mat3 value)
	{
		uniforms[name].Mat3 = value;
	}

	void Material::setMatrix(std::string name, glm::mat4 value)
	{
		uniforms[name].Mat4 = value;
	}

	std::map<std::string, UniformValue>* Material::getUniforms()
	{
		return &uniforms;
	}
}