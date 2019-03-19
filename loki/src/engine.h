namespace Loki
{
	/*Global point of entry for gthe graphics engine
	Starts all the neccesery initialization -
	includes OpenGL function pointers and glad*/
	class Engine
	{
	public:
		void Init();
		void Clean();
		void InitGUI();
		void NewGUIFrame();
		void InputKey();
		void InputMouse();
		void InputScroll();
	}
}