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
		Scene();
		~Scene();
		void loadMesh(Scene& scene, std::string& filename);
			

	public:
		MeshLoader meshloader;
		std::vector<Mesh> meshes;
		std::vector<FreeCamera> cameras;
			
	};
}