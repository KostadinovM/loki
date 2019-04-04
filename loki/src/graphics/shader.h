#include <string>
#include <vector>

namespace Loki
{
	namespace Graphics
	{
		class Shader
		{
		private:		
			std::string readShaderFile(std::string shaderPath);

		public:
			unsigned int ID;
			Shader();
			Shader(std::string vertexPath, std::string fragmentPath);
			void load(std::string vertexShader, std::string fragmentShader);
			void use();
			void setBool(std::string& name, bool value) const;
			void setInt(const std::string& name, int value) const;
			void setFloat(std::string& name, float value) const;
		};
	}
}