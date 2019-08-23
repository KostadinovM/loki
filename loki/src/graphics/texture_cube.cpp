#include "texture_cube.h"
#include "stb_image.h"
#include <iostream>

namespace Loki
{
	TextureCube::TextureCube()
	{
	}

	TextureCube::~TextureCube()
	{
	}

	void TextureCube::loadTextureCube(std::vector<std::string> faces, GLenum type, GLenum wrapS, GLenum wrapT, GLenum wrapR, GLenum filterMin, GLenum filterMax, GLenum texUnit)
	{
		glGenTextures(1, &id);
		this->type = type;
		this->wrapS = wrapS;
		this->wrapT = wrapT;
		this->wrapR = wrapR;
		this->filterMin = filterMin;
		this->filterMax = filterMax;
		this->texUnit = texUnit;

		bind();

		for (size_t i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, filterMin);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, filterMax);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrapT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrapR);
	}

	void TextureCube::bind()
	{
		glActiveTexture(GL_TEXTURE0 + texUnit);
		glBindTexture(type, id);
	}

	void TextureCube::unbind()
	{
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}