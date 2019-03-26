#include <string>

namespace Loki
{
	namespace graphics
	{
		class Shader
		{
		private:

		public:
			Shader();
			Shader(std::string vertexShader = "", std::string fragmentShader = "");
			void load();
			void use();
			void setBool();
			void setInt();
			void setFloat();
		};
	}
}