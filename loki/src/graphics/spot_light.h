#pragma once
#include "light.h"
#include "glm/glm.hpp"

namespace Loki
{
	class SpotLight : public Light
	{
		public:
			glm::vec3 direction;
			glm::vec3 position;
			float innerRadius = 1.0f;
			float outerRadius = 1.0f;

			float constant;
			float linear;
			float quadratic;
	};
}