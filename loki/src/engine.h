#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Loki
{

	/*Global point of entry for gthe graphics engine
	Starts all the neccesery initialization -
	includes OpenGL function pointers and glad*/

		void init(GLFWwindow* window, GLADloadproc loadProc);
		void clean();
		void newGUIFrame();
		void renderGUI();
		void inputKey(int key, int action);
		void inputMouse(int button, int action);
		void inputScroll(float scrollOffset);
	
}