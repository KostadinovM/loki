#include "texture.h"
#include <stb_image.h>
#include <iostream>

namespace Loki
{
	Texture::Texture()
	{

	}

	Texture::Texture(std::string texPath, GLenum texType, GLint texUnit, GLuint texWrapping, GLint texFiltering)
		: path(texPath), type(texType), textureUnit(texUnit), wrap(texWrapping), filter(texFiltering)
	{
		loadTexture(texPath, texType, texWrapping, texFiltering);
	}


	Texture::Texture(const Texture& src)
	{
		path = src.path;
		id = src.id;
		type = src.type;
		filter = src.filter;
		wrap = src.wrap;
		name = src.name;
		width = src.width;
		height = src.height;
		name = src.name;
		data = src.data;
		nrChannels = src.nrChannels;
	}

	Texture::~Texture()
	{
	}

	void Texture::loadTexture(std::string texPath, GLenum texType, GLuint texWrapping, GLint texFiltering)
	{
		glGenTextures(1, &id);
		//stbi_set_flip_vertically_on_load(false);
		const char* c = texPath.c_str();
		data = stbi_load(texPath.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;

			glBindTexture(texType, id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(texType);

			glTexParameteri(texType, GL_TEXTURE_WRAP_S, texWrapping);
			glTexParameteri(texType, GL_TEXTURE_WRAP_T, texWrapping);
			glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, texFiltering);

			stbi_image_free(data);
				
		}
		else 
		{ 
			std::cout << "Failed to load texture" << std::endl;
			stbi_image_free(data);
		}
			
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

	void Texture::setName(std::string texName)
	{
		name = texName;
	}

	std::string Texture::getName()
	{
		return name;
	}
	std::string Texture::getPath()
	{
		return path;
	}
	unsigned char* Texture::getData()
	{
		return data;
	}
}