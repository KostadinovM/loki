#include <string>
#include <glm/glm.hpp>

namespace Loki
{
	class Light
	{
	private:
		std::string lightType;
		glm::vec3 color;
		glm::vec3 direction;
		float intensity;

		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 difuse;
		glm::vec3 specular;

	public:
		Light();
		~Light();
		void setLightType(std::string type);
		void setColor(glm::vec3 color);
		void setDirection(glm::vec3 direction);
		void setIntensity(float intensity);

		std::string getLightType();
		glm::vec3 getColor();
		glm::vec3 getDirection();
		float getIntensity();
			

	};
}