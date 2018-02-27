#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
private:
	//Declare a window object
	StopWatch m_timer;
	static double CursorX;
	static double CursorY;
	static int WindowWidth;
	static int WindowHeight;
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static void SetCursorVisible(bool);
	static double GetCursorX(void);
	static double GetCursorY(void);
	static int GetWindowWidth(void);
	static int GetWindowHeight(void);
};

#endif