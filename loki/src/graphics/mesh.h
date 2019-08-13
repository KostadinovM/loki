#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <shader.h>
#include <texture.h>

namespace Loki
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

	class Mesh
	{
	public:
		GLuint VAO = 0;
		GLuint VBO, EBO;
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uv;
			

		bool texturesOn = true;
		bool indicesOn = true;


	public:
		Mesh();
		~Mesh();
		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
		Mesh(std::vector<glm::vec3> positions, std::vector<GLuint> indices);
		Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<GLuint> indices);
		Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<GLuint> indices, std::vector<glm::vec2> uv);

		void setVertices(std::vector<Vertex> verts);
		void setIndices(std::vector<GLuint> inds);
		void setTextures(std::vector<Texture> texs);
		void disableTextures();
		void disableIndices();
		void enableIndices();
		bool hasTextures();
		void draw(Shader shader);
		void setupSimpleMesh();

	private:
		void setupMesh();

	};
}