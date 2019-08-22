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
		unsigned int globalUBO;

		//config
		bool lights = true;
		bool shadows = false;
		bool stencilTest = false;
		bool blending = false;

		Scene* scene;
		int windowWidth;
		int windowHeight;
		std::vector<Shader> shaders;
		Shader sceneSP;
		Shader meshSP;

	private:
		void renderDirLights();
		void renderPointLights();
		void renderSpotLights();
	};
}