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
		bool bloom = false;
		bool aaliasing = false;
		bool ssao = false;

		glm::mat4 model, view, projection;
		float scaler = 0.01f;
		float locationX = 0.0f;
		float locationY = -1.75f;
		float locationZ = 0.0f;

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