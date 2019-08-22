#pragma once
#include "light.h"
#include <glm/glm.hpp>

namespace Loki
{
	class DirectionalLight : public Light
	{
		public:
			glm::vec3 direction;
	};
}