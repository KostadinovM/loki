#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.h"

namespace Loki
{

	/*
	Starts neccesery initialization -
	includes OpenGL function pointers and glad*/

	Renderer* init(GLFWwindow* window, GLADloadproc loadProc);
	void clean();
	void newGUIFrame();
	void renderGUI();
	void inputKey(int key, int action);
	void inputMouse(int button, int action);
	void inputScroll(float scrollOffset);
	void rendering();
}