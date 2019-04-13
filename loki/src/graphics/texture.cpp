#include "texture.h"
#include <stb_image.h>
#include <iostream>

namespace Loki
{
	namespace Graphics
	{
		Texture::Texture()
		{

		}

		Texture::Texture(std::string texPath, GLenum texType, GLint texUnit, GLuint texWrapping, GLint texFiltering)
			: type(texType), textureUnit(texUnit)
		{
			loadTexture(texPath, texType, texWrapping, texFiltering);
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &id);
		}

		void Texture::loadTexture(std::string texPath, GLenum texType, GLuint texWrapping, GLint texFiltering)
		{
			glGenTextures(1, &id);
			glBindTexture(texType, id);

			glTexParameteri(texType, GL_TEXTURE_WRAP_S, texWrapping);
			glTexParameteri(texType, GL_TEXTURE_WRAP_T, texWrapping);

			glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, texFiltering);
			glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, texFiltering);

			stbi_set_flip_vertically_on_load(true);
			const char* c = texPath.c_str();
			data = stbi_load(texPath.c_str(), &width, &height, &nrChannels, 0);
			if (data && texType == GL_TEXTURE_2D)
			{
				glTexImage2D(texType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(texType);
			}
			else { std::cout << "Failed to load texture" << std::endl; }	
			stbi_image_free(data);
		}

		void Texture::bind()
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(type, id);
		}

		void Texture::unbind()
		{
			glActiveTexture(0);
			glBindTexture(type, 0);
		}

		GLuint Texture::getID()
		{
			return id;
		}

		GLenum Texture::getType()
		{
			return type;
		}

		GLint Texture::getTexUnit()
		{
			return textureUnit;
		}
	}
}