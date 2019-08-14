#include "scene.h"

namespace Loki
{
	Scene::Scene()
	{
		meshloader = MeshLoader();
	}

	Scene::~Scene()
	{

	}

	void Scene::loadMeshes(std::string filename)
	{
		meshloader = MeshLoader(filename);
	}
}