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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	scene = Loki::Scene();
	scene.mainCamera = camera;
	renderer = Loki::init(window, GLADloadproc(glfwGetProcAddress));
	scene.loadMeshes(R"(C:\Users\Faust\Desktop\Engine\loki\resources\models\nanosuit\nanosuit.obj)");
	Loki::Cube cube;
	cube.disableTextures();
	scene.meshes.push_back(cube);
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