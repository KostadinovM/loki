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
		void InputKey(int key, int action);
		void InputMouse(int button, int action);
		void InputScroll();
	};
}