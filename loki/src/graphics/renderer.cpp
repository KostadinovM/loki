#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

namespace Loki
{
	Renderer::Renderer()
	{
		scene = nullptr;
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Init(Scene* scene)
	{
		this->scene = scene;
		sceneSP = Shader(R"(C:\Users\Faust\Desktop\Engine\loki\resources\shaders\light_vs.glsl)",
			R"(C:\Users\Faust\Desktop\Engine\loki\resources\shaders\light_fs.glsl)");
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
		projection = glm::perspective(glm::radians(maincamera.zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
		view = maincamera.getViewMatrix();

		sceneSP.use();
		sceneSP.setVector("viewPos", maincamera.getCameraPos());
		if (lights)
		{
			sceneSP.setInt("lightmode", 0);
			sceneSP.setInt("numDirLights", scene->directionalLights.size());
			sceneSP.setInt("numPointLights", scene->pointLights.size());
			sceneSP.setInt("numSpotLights", scene->spotlights.size());

			renderDirLights();
			renderPointLights();
			renderSpotLights();
		}
		else
			sceneSP.setInt("lightmode", 1);

		sceneSP.setFloat("material.shininess", 64.0f);

		sceneSP.setMatrix("projection", projection);
		sceneSP.setMatrix("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(locationX, locationY, locationZ)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(scaler, scaler, scaler));	
		sceneSP.setMatrix("model", model);
		scene->meshloader.draw(sceneSP);


		//mesh shader
		meshSP.use();
		meshSP.setMatrix("projection", projection);
		meshSP.setMatrix("view", view);

		for (size_t i = 0; i < scene->meshes.size(); i++)
		{
			for (size_t j = 0; j < scene->pointLights.size(); j++)
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, scene->pointLights[j].position);
				model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
				meshSP.setMatrix("model", model);

				scene->meshes[i].disableIndices();
				scene->meshes[i].draw(meshSP);
				scene->meshes[i].enableIndices();
			}
		}

		//TO-DO: get rid of this hard-coded mess:
		for (size_t i = 0; i < scene->spotlights.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, scene->spotlights[i].position);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			meshSP.setMatrix("model", model);

			scene->meshes[4].disableIndices();
			scene->meshes[4].draw(meshSP);
			scene->meshes[4].enableIndices();
		}
	}

	void Renderer::renderDirLights()
	{
		if (scene->directionalLights.size() > 0)
		{
			for (size_t i = 0; i < scene->directionalLights.size(); i++)
			{
				//render directional lights
				std::string attrIndex = "dirLights[" + std::to_string(i) + "]";

				sceneSP.setVector(attrIndex + std::string(".direction"), scene->directionalLights[i].direction);
				sceneSP.setVector(attrIndex + std::string(".ambient"), scene->directionalLights[i].ambient);
				sceneSP.setVector(attrIndex + std::string(".diffuse"), scene->directionalLights[i].diffuse);
				sceneSP.setVector(attrIndex + std::string(".specular"), scene->directionalLights[i].specular);
			}
		}
	}

	void Renderer::renderPointLights()
	{
		if (scene->pointLights.size() > 0)
		{
			for (size_t i = 0; i < scene->pointLights.size(); i++)
			{
				//render point lights
				std::string attrIndex = "pointLights[" + std::to_string(i) + "]";
				sceneSP.setVector(attrIndex + std::string(".position"), scene->pointLights[i].position);

				//check for atennuation
				sceneSP.setFloat(attrIndex + std::string(".constant"), scene->pointLights[i].constant);
				sceneSP.setFloat(attrIndex + std::string(".linear"), scene->pointLights[i].linear);
				sceneSP.setFloat(attrIndex + std::string(".quadratic"), scene->pointLights[i].quadratic);

				sceneSP.setVector(attrIndex + std::string(".ambient"), scene->pointLights[i].ambient);
				sceneSP.setVector(attrIndex + std::string(".diffuse"), scene->pointLights[i].diffuse);
				sceneSP.setVector(attrIndex + std::string(".specular"), scene->pointLights[i].specular);
			}
		}
	}

	void Renderer::renderSpotLights()
	{
		if (scene->spotlights.size() > 0)
		{
			for (size_t i = 0; i < scene->spotlights.size(); i++)
			{
				//render spot lights
				std::string attrIndex = "spotLights[" + std::to_string(i) + "]";
				sceneSP.setVector(attrIndex + std::string(".position"), scene->spotlights[i].position);
				sceneSP.setVector(attrIndex + std::string(".direction"), scene->spotlights[i].direction);
				sceneSP.setFloat(attrIndex + std::string(".cutOff"), scene->spotlights[i].innerRadius);
				sceneSP.setFloat(attrIndex + std::string(".outerCutOff"), scene->spotlights[i].outerRadius);

				//check for atennuation
				sceneSP.setFloat(attrIndex + std::string(".constant"), scene->spotlights[i].constant);
				sceneSP.setFloat(attrIndex + std::string(".linear"), scene->spotlights[i].linear);
				sceneSP.setFloat(attrIndex + std::string(".quadratic"), scene->spotlights[i].quadratic);

				sceneSP.setVector(attrIndex + std::string(".ambient"), scene->spotlights[i].ambient);
				sceneSP.setVector(attrIndex + std::string(".diffuse"), scene->spotlights[i].diffuse);
				sceneSP.setVector(attrIndex + std::string(".specular"), scene->spotlights[i].specular);
			}
		}
	}
}


