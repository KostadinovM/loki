#include "fly_camera.h"

namespace Loki
{
	namespace Graphics
	{
		FlyCamera::FlyCamera(glm::vec3 position, glm::vec3 forward, glm::vec3 up)
		{
			this->position = position;
			this->forward = forward;
			this->up = up;
		}

		void FlyCamera::Update()
		{
			glm::vec3 forward;
			forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			forward.y = sin(glm::radians(pitch));
			forward.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));
			this->forward = glm::normalize(forward);

			this->right = glm::normalize(glm::cross(this->forward, this->up));
			this->up = glm::normalize(glm::cross(this->right, this->forward));

			UpdateViewMatrix();
		}

		void FlyCamera::InputKey(float deltaTime, CAMERA_MOVEMENT direction)
		{
			float velocity = movementSpeed * deltaTime;
			if (direction == FORWARD)
				position += forward * velocity;
			if (direction == BACKWARD)
				position -= forward * velocity;
			if (direction == LEFT)
				position -= right * velocity;
			if (direction == RIGHT)
				position += right * velocity;
		}

		void FlyCamera::InputMouse(float deltaX, float deltaY, GLboolean constrainPitch)
		{
			float xmovement = deltaX * mouseSensitivity;
			float ymovement = deltaY * mouseSensitivity;

			yaw += xmovement;
			pitch += ymovement;

			// Make sure that when pitch is out of bounds, screen doesn't get flipped(checks if the pitch is 
			// above or bellow 90 degrees(if it is, it would break the lookAt calculation)
			if (constrainPitch)
			{
				if (pitch > 89.0f)
					pitch = 89.0f;
				if (pitch < -89.0f)
					pitch = -89.0f;
			}
		}

		void FlyCamera::InputScroll(float yoffset)
		{
			if (zoom >= 1.0f && zoom <= 45.0f)
				zoom -= yoffset;
			if (zoom <= 1.0f)
				zoom = 1.0f;
			if (zoom >= 45.0f)
				zoom = 45.0f;
		}
	}
}
