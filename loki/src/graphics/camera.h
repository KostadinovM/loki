#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Loki
{
	namespace Graphics
	{
		class Camera
		{
		private:

		public:
			glm::vec3 Position;
			glm::vec3 Forward;
			glm::vec3 Up;
			glm::mat4 View;

			Camera();
			Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);
			void UpdateViewMatrix();
		};
	}
}