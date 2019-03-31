#include <glm/vec3.hpp>

namespace Loki
{
	namespace Graphics
	{
		class Camera
		{
		private:
			glm::vec3 Position;
			glm::vec3 Front;
			glm::vec3 Up;
			glm::vec3 Right;
			glm::vec3 WorldUp;

		public:
			Camera();
			Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);
			void UpdateViewMatrix();
		};
	}
}