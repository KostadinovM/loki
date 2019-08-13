#include "mesh.h"
#include <string>
namespace Loki
{
	Mesh::Mesh()
	{

	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) : 
		vertices(vertices), indices(indices)
	{
		setupMesh();
	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) :
		vertices(vertices), indices(indices), textures(textures)
	{
		setupMesh();
	}

	Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<GLuint> indices) :
		positions(positions), indices(indices)
	{
		setupSimpleMesh();
	}

	Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<GLuint> indices) :
		positions(positions), normals(normals), indices(indices)
	{
		setupSimpleMesh();
	}

	Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<GLuint> indices, std::vector<glm::vec2> uv) :
		positions(positions), normals(normals), indices(indices), uv(uv)
	{
		setupSimpleMesh();
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::setVertices(std::vector<Vertex> verts)
	{
		vertices = verts;
	}

	void Mesh::setIndices(std::vector<GLuint> inds)
	{
		indices = inds;
	}

	void Mesh::setTextures(std::vector<Texture> texs)
	{
		textures = texs;
	}

	void Mesh::disableTextures()
	{
		texturesOn = false;
	}

	void Mesh::disableIndices()
	{
		indicesOn = false;
	}

	void Mesh::enableIndices()
	{
		indicesOn = true;
	}

	bool Mesh::hasTextures()
	{
		return texturesOn;
	}

	void Mesh::draw(Shader shader)
	{
		if (hasTextures())
		{
			// bind appropriate textures
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			unsigned int normalNr = 1;
			unsigned int heightNr = 1;
			for (unsigned int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
				// retrieve texture number (the N in diffuse_textureN)
				std::string number;
				std::string name = textures[i].getName();
				if (name == "texture_diffuse")
					number = std::to_string(diffuseNr++);
				else if (name == "texture_specular")
					number = std::to_string(specularNr++); // transfer unsigned int to stream
				else if (name == "texture_normal")
					number = std::to_string(normalNr++); // transfer unsigned int to stream
				else if (name == "texture_height")
					number = std::to_string(heightNr++); // transfer unsigned int to stream

															// now set the sampler to the correct texture unit
				glUniform1i(glGetUniformLocation(shader.getID(), ("material." + name + number).c_str()), i);
				// and finally bind the texture
				glBindTexture(GL_TEXTURE_2D, textures[i].getID());
			}
		}
			glBindVertexArray(VAO);
			if(indicesOn)
				glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			else
				glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
	}

	void Mesh::setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));

		//// vertex tangent
		//glEnableVertexAttribArray(3);
		//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		//// vertex bitangent
		//glEnableVertexAttribArray(4);
		//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));


		glBindVertexArray(0);
	}

	void Mesh::setupSimpleMesh()
	{
		if (!VAO)
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
		}

		std::vector<float> vertexData;
		for (int i = 0; i < positions.size(); i++)
		{
			vertexData.push_back(positions[i].x);
			vertexData.push_back(positions[i].y);
			vertexData.push_back(positions[i].z);
			if (normals.size() > 0)
			{
				vertexData.push_back(normals[i].x);
				vertexData.push_back(normals[i].y);
				vertexData.push_back(normals[i].z);
			}
			if (uv.size()>0)
			{
				vertexData.push_back(uv[i].x);
				vertexData.push_back(uv[i].y);
			}
		}

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);

		if (indices.size() > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		}

		//calculating the stride
		size_t stride = 3 * sizeof(float);
		if (normals.size() > 0) stride += 3 * sizeof(float);
		if (uv.size() > 0)		stride += 2 * sizeof(float);

		size_t offset = 0;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
		offset += 3 * sizeof(float);

		if (normals.size() > 0)
		{
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 3 * sizeof(float);
		}

		if (uv.size() > 0)
		{
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 2 * sizeof(float);
		}

		glBindVertexArray(0);
	}

		
}