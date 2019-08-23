#include "glad/glad.h"
#include <vector>
#include "string"

namespace Loki
{
	class TextureCube
	{
	public:
		GLuint id;
		GLenum wrapS;
		GLenum wrapT;
		GLenum wrapR;
		GLenum filterMin;
		GLenum filterMax;
		GLenum type;
		GLenum texUnit;

		int width;
		int height;
		int nrChannels;

	public:
		TextureCube();
		~TextureCube();
		
		void loadTextureCube(std::vector<std::string> faces, GLenum type, GLenum wrapS, GLenum wrapT, GLenum wrapR, GLenum filterMin, GLenum filterMax, GLenum texUnit);
		void bind();
		void unbind();
	};
}