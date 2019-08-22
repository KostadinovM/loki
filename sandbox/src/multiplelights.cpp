#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>
#include "loki.h"
#include "graphics/shader.h"
#include <glm/vec3.hpp>
#include <stb_image.h>
#include "graphics/texture.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "graphics/camera.h"
#include "graphics/free_camera.h"
#include "mesh_loader.h"
#include "cube.h"
#include "mesh.h"
#include "scene.h"
#include "renderer.h"
#include "spot_light.h"
#include "directional_light.h"
#include "point_light.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

//setup
Loki::Scene scene;
Loki::Renderer* renderer;
Loki::FreeCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));


// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool keysPressed[1024];
bool keysActive[1024];
// lighting
glm::vec3 lightPos(1.2f, 1.0f, 1.0f);

int main()
{
	//Window setup: 
	// glfw: initialize and configure
	// ------------------------------
	if (!glfwInit())
		glfwTerminate();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Loki Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//make lights
	Loki::DirectionalLight dirlight1;
	dirlight1.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	dirlight1.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	dirlight1.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
	dirlight1.specular = glm::vec3(0.5f, 0.5f, 0.5f);

	glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
	};

	Loki::PointLight pointLight1;
	pointLight1.position = glm::vec3(0.7f, 0.2f, 2.0f);
	pointLight1.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	pointLight1.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	pointLight1.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight1.constant = 1.0f;
	pointLight1.linear = 0.09f;
	pointLight1.quadratic = 0.032f;

	Loki::PointLight pointLight2;
	pointLight2.position = glm::vec3(2.3f, -3.3f, -4.0f);
	pointLight2.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	pointLight2.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	pointLight2.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight2.constant = 1.0f;
	pointLight2.linear = 0.09f;
	pointLight2.quadratic = 0.032f;

	Loki::PointLight pointLight3;
	pointLight3.position = glm::vec3(-4.0f, 2.0f, -12.0f);
	pointLight3.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	pointLight3.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	pointLight3.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight3.constant = 1.0f;
	pointLight3.linear = 0.09f;
	pointLight3.quadratic = 0.032f;

	Loki::PointLight pointLight4;
	pointLight4.position = glm::vec3(0.0f, 0.0f, -3.0f);
	pointLight4.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	pointLight4.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	pointLight4.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight4.constant = 1.0f;
	pointLight4.linear = 0.09f;
	pointLight4.quadratic = 0.032f;

	Loki::SpotLight spotlight1;
	spotlight1.position = glm::vec3(-2.0f, 0.0f, 0.0f);
	spotlight1.direction = glm::vec3(1.0f, 0.0f, 0.0f);
	spotlight1.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	spotlight1.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	spotlight1.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	spotlight1.constant = 1.0f;
	spotlight1.linear = 0.09f;
	spotlight1.quadratic = 0.032f;
	spotlight1.innerRadius = glm::cos(glm::radians(12.5f));
	spotlight1.outerRadius = glm::cos(glm::radians(15.0f));

	scene = Loki::Scene();

	scene.directionalLights.push_back(dirlight1);
	scene.pointLights.push_back(pointLight1);
	scene.pointLights.push_back(pointLight2);
	scene.pointLights.push_back(pointLight3);
	scene.pointLights.push_back(pointLight4);
	scene.spotlights.push_back(spotlight1);

	scene.mainCamera = camera;
	renderer = Loki::init(window, GLADloadproc(glfwGetProcAddress));
	//scene.loadMeshes(R"(C:\Users\Faust\Desktop\Engine\loki\resources\models\nanosuit\nanosuit.obj)");
	scene.loadMeshes(R"(C:\Users\Faust\Desktop\Engine\loki\resources\models\sponza\sponza.obj)");
	Loki::Cube cube1;
	Loki::Cube cube2;
	Loki::Cube cube3;
	Loki::Cube cube4;
	Loki::Cube cube5;
	cube1.disableTextures();
	cube2.disableTextures();
	cube3.disableTextures();
	cube4.disableTextures();
	cube5.disableTextures();
	scene.meshes.push_back(cube1);
	scene.meshes.push_back(cube2);
	scene.meshes.push_back(cube3);
	scene.meshes.push_back(cube4);
	scene.meshes.push_back(cube5);
	glEnable(GL_DEPTH_TEST);
	


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	renderer->Init(&scene);
	renderer->Resize(800, 600);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		Loki::newGUIFrame();

		// per-frame time logic
				// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		//scene.mainCamera.updateView();
		renderer->Render();

		Loki::renderGUI();
		Loki::rendering();
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
	}

	Loki::clean();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		scene.mainCamera.InputKey(deltaTime, Loki::CAMERA_MOVEMENT::FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		scene.mainCamera.InputKey(deltaTime, Loki::CAMERA_MOVEMENT::BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		scene.mainCamera.InputKey(deltaTime, Loki::CAMERA_MOVEMENT::LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		scene.mainCamera.InputKey(deltaTime, Loki::CAMERA_MOVEMENT::RIGHT);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	renderer->Resize(width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keysPressed[key] = true;
		else if (action == GLFW_RELEASE)
		{
			keysPressed[key] = false;
			keysActive[key] = false;
		}
	}
	Loki::inputKey(key, action);
}

bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;  // reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	scene.mainCamera.InputMouse(xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Loki::inputMouse(button, action);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Loki::inputScroll(yoffset);
	camera.InputScroll(yoffset);
}