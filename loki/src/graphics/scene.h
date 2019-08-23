#pragma once
#include "mesh_loader.h"
#include "camera.h"
#include "free_camera.h"
#include <string>
#include "point_light.h"
#include "spot_light.h"
#include "directional_light.h"
#include "skybox.h"

namespace Loki
{
	class Scene 
	{
	public:
		MeshLoader meshloader;
		std::vector<Mesh> meshes;
		std::vector<FreeCamera> cameras;
		FreeCamera mainCamera;
		std::vector<PointLight> pointLights;
		std::vector<DirectionalLight> directionalLights;
		std::vector<SpotLight> spotlights;
		Skybox skybox;


	public:
		Scene();
		~Scene();
		void loadMeshes(std::string filename);
	};
}