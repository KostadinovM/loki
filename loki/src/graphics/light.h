#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Loki
{
	class Light
	{
	public:
		//std::string lightType;
		//glm::vec3 direction;

		//glm::vec3 position;

		glm::vec3 color;
		float intensity = 1.0f;
		bool visible = true;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

	};
}