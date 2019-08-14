#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Loki
{
	Renderer::Renderer()
	{
		
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Init(Scene* scene)
	{
		this->scene = scene;
		sceneSP = Shader(R"(C:\Users\Faust\Desktop\Engine\loki\resources\shaders\modellight_vs.glsl)",
			R"(C:\Users\Faust\Desktop\Engine\loki\resources\shaders\modellight_fs.glsl)");
		meshSP = Shader(R"(C:\Users\Faust\Desktop\Engine\loki\resources\shaders\lamp_vs.glsl)",
			R"(C:\Users\Faust\Desktop\Engine\loki\resources\shaders\lamp_fs.glsl)");
	}

	void Renderer::Resize(int width, int height)
	{
		windowWidth = width;
		windowHeight = height;
	}

	void Renderer::Render()
	{
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FreeCamera maincamera = scene->mainCamera;
		maincamera.updateView();
		glm::mat4 projection = glm::perspective(glm::radians(maincamera.zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
		glm::mat4 view = maincamera.getViewMatrix();

		//scene shader
		sceneSP.use();
		sceneSP.setVector("light.position", glm::vec3(1.2f, 1.0f, 1.0f));
		sceneSP.setVector("viewPos", maincamera.getCameraPos());

		// light properties
		sceneSP.setVector("light.ambient", glm::vec3(0.3f, 0.3f, 0.3f));
		sceneSP.setVector("light.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		sceneSP.setVector("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		// material properties
		sceneSP.setFloat("material.shininess", 64.0f);

		sceneSP.setMatrix("projection", projection);
		sceneSP.setMatrix("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		sceneSP.setMatrix("model", model);
		scene->meshloader.draw(sceneSP);

		//mesh shader
		meshSP.use();
		meshSP.setMatrix("projection", projection);
		meshSP.setMatrix("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.2f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		meshSP.setMatrix("model", model);

		for (int i = 0; i < scene->meshes.size(); i++)
		{
			scene->meshes[i].disableIndices();
			scene->meshes[i].draw(meshSP);
			scene->meshes[i].enableIndices();
		}
	}
}


