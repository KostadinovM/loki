#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Loki
{
		class Camera
		{
		private:

		public:
			glm::vec3 position = glm::vec3(0.0, 0.0f, 0.1f);
			glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
			glm::vec3 worldUp;

			glm::mat4 view;

			Camera();
			Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);
			void UpdateViewMatrix();
			glm::mat4 getViewMatrix() const;
		};
}