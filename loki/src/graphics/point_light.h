#pragma once
#include "light.h"
#include "glm/glm.hpp"

namespace Loki
{
	class PointLight : public Light
	{
		public:
			glm::vec3 position;

			float constant;
			float linear;
			float quadratic;
	};
}