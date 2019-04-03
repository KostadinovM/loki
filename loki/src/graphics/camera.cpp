#include "camera.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Loki
{
	namespace Graphics
	{
		Camera::Camera()
		{
		}

		Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up)
			: Position(position), Forward(forward), Up(up)
		{
			UpdateViewMatrix();
		}

		void Camera::UpdateViewMatrix()
		{
			View = glm::lookAt(Position, Position + Forward, Up);
		}
	}
}