#pragma once
#include "mesh_loader.h"
#include "camera.h"
#include "free_camera.h"
#include <string>

namespace Loki
{
	class Scene 
	{
	public:
		MeshLoader meshloader;
		std::vector<Mesh> meshes;
		std::vector<FreeCamera> cameras;
		FreeCamera mainCamera;

	public:
		Scene();
		~Scene();
		void loadMeshes(std::string filename);
	};
}