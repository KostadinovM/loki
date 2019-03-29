#include <string>
#include <vector>

namespace Loki
{
	namespace Graphics
	{
		class Shader
		{
		private:
			unsigned int ID;

		public:
			Shader();
			Shader(std::string vertexShader = "", std::string fragmentShader = "");
			void load(std::string vertexShader, std::string fragmentShader);
			void use();
			void setBool(std::string name, bool value);
			void setInt(std::string name, int value);
			void setFloat(std::string name, float value);
		};
	}
}