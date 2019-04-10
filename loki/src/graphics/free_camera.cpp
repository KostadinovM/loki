#include "free_camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Loki
{
	namespace Graphics
	{
		FreeCamera::FreeCamera(glm::vec3 position, glm::vec3 forward, glm::vec3 up)
		{
			this->forward = forward;
			this->position = position;
			this->worldUp = up;

			updateView();
		}

		void FreeCamera::updateView()
		{
			glm::vec3 forward;
			forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			forward.y = sin(glm::radians(pitch));
			forward.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));
			this->forward = glm::normalize(forward);

			this->right = glm::normalize(glm::cross(this->forward, this->worldUp));
			this->up = glm::normalize(glm::cross(this->right, this->forward));

			UpdateViewMatrix();
		}

		glm::mat4 FreeCamera::getViewMatrix()
		{
			return this->view;
		}

		void FreeCamera::InputKey(float deltaTime, CAMERA_MOVEMENT direction)
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

		void FreeCamera::InputMouse(float xoffset, float yoffset, GLboolean constrainPitch)
		{
			xoffset *= mouseSensitivity;
			yoffset *= mouseSensitivity;

			yaw += xoffset;
			pitch += yoffset;

			// Make sure that when pitch is out of bounds, screen doesn't get flipped
			if (constrainPitch)
			{
				if (pitch > 89.0f)
					pitch = 89.0f;
				if (pitch < -89.0f)
					pitch = -89.0f;
			}

			// Update Front, Right and Up Vectors using the updated Euler angles
			updateView();
		}

		void FreeCamera::InputScroll(float yoffset)
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
