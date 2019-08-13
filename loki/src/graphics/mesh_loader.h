#pragma once
#include <shader.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <mesh.h>
#include <glm/glm.hpp>

namespace Loki
{
	class MeshLoader
	{
	public:
		MeshLoader();
		MeshLoader(std::string path);
		~MeshLoader();
		void loadMesh(std::string path);
		void draw(Shader shader);

	private:
		std::vector<Mesh> meshStore;
		std::vector<Texture> textureStore;
		std::string directory;
		GLuint texUnit;

		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);

		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	};
}