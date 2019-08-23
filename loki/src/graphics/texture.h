#pragma once
#include <string>
#include <glad/glad.h>

namespace Loki
{
	class Texture
	{
	public:
		GLuint id;
		int width;
		int height;
		int nrChannels;
		unsigned char* data;
		std::string name;
		std::string path;
		GLenum type;
		GLenum textureUnit;
		GLenum wrap;
		GLenum filter;
			

	public:
			
		Texture();
		Texture(std::string texPath, GLenum texType, GLint texUnit, GLuint texWrapping, GLint texFiltering);
		Texture(const Texture& src);
		~Texture();
		void loadTexture(std::string texPath, GLenum texType, GLuint texWrapping, GLint texFiltering);
		void bind();
		void unbind();
		GLuint getID();
		GLenum getType();
		GLint getTexUnit();
		void setName(std::string texName);
		std::string getName();
		std::string getPath();
		unsigned char* getData();
	};
}