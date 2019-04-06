#include <string>
#include <glad/glad.h>

namespace Loki
{
	namespace Graphics
	{
		class Texture
		{
		private:
			GLuint id;
			int width;
			int height;
			int nrChannels;
			unsigned char* data;
			GLenum type;
			GLint textureUnit;

		public:
			Texture();
			Texture(std::string texPath, GLenum texType, GLint texUnit, GLuint texWrapping, GLint texFiltering);
			~Texture();
			void loadTexture(std::string texPath, GLenum texType, GLuint texWrapping, GLint texFiltering);
			void bind();
			void unbind();
			GLuint getID() const;
			GLenum getType() const;
			GLint getTexUnit() const;
		};
	}
}