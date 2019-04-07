#pragma once
#include "camera.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Loki 
{
	namespace Graphics
	{
		enum CAMERA_MOVEMENT
		{
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT
		};

		//Derived from Camera class - to serve as a free mode camera
		class FlyCamera : Camera
		{
		public:
			float yaw;
			float pitch;

			float movementSpeed = 10.0f;
			float mouseSensitivity = 0.1f;
			float zoom = 45.0f;

		public:
			FlyCamera(glm::vec3 position, glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
			void Update();
			virtual void InputKey(float deltaTime, CAMERA_MOVEMENT direction);
			virtual void InputMouse(float deltaX, float deltaY,  GLboolean constrainPitch = true);
			virtual void InputScroll(float yoffset);
		};
	}
}
