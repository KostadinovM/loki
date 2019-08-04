//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include <imgui.h>
//#include "loki.h"
//#include "graphics/shader.h"
//#include <glm/vec3.hpp>
//#include <stb_image.h>
//#include "graphics/texture.h"
//#include <glm/mat4x4.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "graphics/camera.h"
//#include "graphics/free_camera.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 1200;
//const unsigned int SCR_HEIGHT = 900;
//
//// camera 
//Loki::Graphics::FreeCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//
//// timing
//float deltaTime = 0.0f;	// time between current frame and last frame
//float lastFrame = 0.0f;
//
//bool keysPressed[1024];
//bool keysActive[1024];
//// lighting
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//int main()
//{
//	//Window setup: 
//	// glfw: initialize and configure
//	// ------------------------------
//	if (!glfwInit())
//		glfwTerminate();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
//	// glfw window creation
//	// --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, cursor_position_callback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	glEnable(GL_DEPTH_TEST);
//
//	// build and compile our shader program
//	// ------------------------------------
//	Loki::Graphics::Shader lightingShader(R"(C:\Users\Faust\Desktop\Engine\loki\resources\shaders\light_vs.glsl)",
//		R"(C:\Users\Faust\Desktop\Engine\loki\resources\shaders\light_fs.glsl)");
//
//	Loki::Graphics::Shader lampShader(R"(C:\Users\Faust\Desktop\Engine\loki\resources\shaders\lamp_vs.glsl)",
//		R"(C:\Users\Faust\Desktop\Engine\loki\resources\shaders\lamp_fs.glsl)");
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//   // ------------------------------------------------------------------
//	float vertices[] = {
//		// positions          // normals           // texture coords
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
//	};
//	// first, configure the cube's VAO (and VBO)
//	unsigned int VBO, cubeVAO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &VBO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindVertexArray(cubeVAO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
//	unsigned int lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	Loki::Graphics::Texture texture1(R"(C:\Users\Faust\Desktop\Engine\loki\resources\textures\container.jpg)", GL_TEXTURE_2D, 0, GL_REPEAT, GL_LINEAR);
//	Loki::Graphics::Texture texture2(R"(C:\Users\Faust\Desktop\Engine\loki\resources\textures\container2.jpg)", GL_TEXTURE_2D, 1, GL_REPEAT, GL_LINEAR);
//
//	// shader configuration
//	// --------------------
//	lightingShader.use();
//	lightingShader.setInt("material.diffuse", texture1.getTexUnit());
//	lightingShader.setInt("material.specular", texture2.getTexUnit());
//
//	Loki::init(window, GLADloadproc(glfwGetProcAddress));
//
//	// render loop
//	// -----------
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//		Loki::newGUIFrame();
//
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);
//
//		// render
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
//
//		
//		lightingShader.use();
//		lightingShader.setVector("light.position", lightPos);
//		lightingShader.setVector("viewPos", camera.getCameraPos());
//
//		// light properties
//		lightingShader.setVector("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
//		lightingShader.setVector("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
//		lightingShader.setVector("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
//
//		// material properties
//		lightingShader.setFloat("material.shininess", 64.0f);
//
//		// create transformations
//		glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.getViewMatrix();
//
//		camera.updateView();
//		// pass transformation matrices to the shader
//		lightingShader.setMatrix("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//		lightingShader.setMatrix("view", view);
//		
//		glm::mat4 model = glm::mat4(1.0);
//		lightingShader.setMatrix("model", model);
//		
//		texture1.bind();
//		texture2.bind();
//
//		glBindVertexArray(cubeVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		lampShader.use();
//		lampShader.setMatrix("projection", projection);
//		lampShader.setMatrix("view", view);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, lightPos);
//		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
//		lampShader.setMatrix("model", model);
//
//		glBindVertexArray(lightVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//		Loki::renderGUI();
//		Loki::rendering();
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//	}
//
//	Loki::clean();
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//// ------------------------------------------------------------------------
//	glDeleteVertexArrays(1, &cubeVAO);
//	glDeleteVertexArrays(1, &lightVAO);
//	glDeleteBuffers(1, &VBO);
//
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.InputKey(deltaTime, Loki::Graphics::CAMERA_MOVEMENT::FORWARD);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.InputKey(deltaTime, Loki::Graphics::CAMERA_MOVEMENT::BACKWARD);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.InputKey(deltaTime, Loki::Graphics::CAMERA_MOVEMENT::LEFT);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.InputKey(deltaTime, Loki::Graphics::CAMERA_MOVEMENT::RIGHT);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow * window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
//{
//
//	if (key >= 0 && key < 1024)
//	{
//		if (action == GLFW_PRESS)
//			keysPressed[key] = true;
//		else if (action == GLFW_RELEASE)
//		{
//			keysPressed[key] = false;
//			keysActive[key] = false;
//		}
//	}
//	Loki::inputKey(key, action);
//}
//
//bool firstMouse = true;
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;  // reversed since y-coordinates go from bottom to left
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.InputMouse(xoffset, yoffset);
//}
//
//void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
//{
//	Loki::inputMouse(button, action);
//}
//
//void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
//{
//	Loki::inputScroll(yoffset);
//	camera.InputScroll(yoffset);
//}