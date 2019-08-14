#pragma once
#include <glad/glad.h>
#include "scene.h"
#include <vector>

namespace Loki
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		void Init(Scene* scene);
		void Resize(int width, int height);
		void Render();

	public:
		//config
		bool lights;
		bool shadows;

		Scene* scene;
		int windowWidth;
		int windowHeight;
		std::vector<Shader> shaders;
		Shader sceneSP;
		Shader meshSP;
	};
}