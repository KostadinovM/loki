#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Loki
{

	/*Global point of entry for gthe graphics engine
	Starts all the neccesery initialization -
	includes OpenGL function pointers and glad*/

		void Init(GLFWwindow* window, GLADloadproc loadProc);
		void Clean();
		void NewGUIFrame();
		void RenderGUI();
		void InputKey(int key, int action);
		void InputMouse(int button, int action);
		void InputScroll(float scrollOffset);
	
}