#include "mesh_loader.h"
namespace Loki
{
	namespace Graphics
	{
		MeshLoader::MeshLoader()
		{
		}

		MeshLoader::~MeshLoader()
		{
		}

		void MeshLoader::loadMesh(std::string path)
		{
			Assimp::Importer import;
			const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ASSIMP ERROR: " << import.GetErrorString() << std::endl;
				return;
			}
			
			directory = path.substr(0, path.find_last_of('/'));
			processNode(scene->mRootNode, scene);
		}

		void MeshLoader::draw(Shader shader)
		{
		}

		void MeshLoader::processNode(aiNode* node, const aiScene* scene)
		{
			//process all the node's meshes (if any)
			for (size_t i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshStore.push_back(processMesh(mesh, scene));
			}

			//then the same for each of its children
			for (size_t i = 0; i < node->mNumChildren; i++)
			{
				processNode(node->mChildren[i], scene);
			}
		}

		Mesh MeshLoader::processMesh(aiMesh* mesh, const aiScene* scene)
		{
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;
			std::vector<Texture> textures;

			for (size_t i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;

				//process vertex positions, normals and uvs
				glm::vec3 vector;
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.position = vector;

				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;

				if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
				{
					glm::vec2 vec;
					vec.x = mesh->mTextureCoords[0][i].x;
					vec.y = mesh->mTextureCoords[0][i].y;
					vertex.uv = vec;
				}
				else
					vertex.uv = glm::vec2(0.0f, 0.0f);

				vertices.push_back(vertex);
			}

			//process indices
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			//process material
			if (mesh->mMaterialIndex >= 0)
			{

			}

			return Mesh(vertices, indices, textures);
		}

		std::vector<Texture> MeshLoader::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
		{
			std::vector<Texture> textures;
			
			return textures;
		}
	}
}