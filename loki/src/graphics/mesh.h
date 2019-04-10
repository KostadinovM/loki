#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <shader.h>
#include <texture.h>

namespace Loki
{
	namespace Graphics
	{
		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 uv;
		};

		class Mesh
		{
		private:
			GLuint VAO, VBO, EBO;
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;
			std::vector<Texture> textures;

		public:

			Mesh();
			~Mesh();
			Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
			Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

			void draw(Shader shader);

		private:
			void setupMesh();
			void setupTexture();
		};


	}
}