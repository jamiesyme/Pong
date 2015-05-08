#pragma once

#include <vector>
class Screen;
class Paddle;


class Game {
public:
	static void Run();
	static void Quit();
	
	static void PushNewScreen(Screen* screen);
	static void PopNewScreen();
	static Screen* GetTopScreen();
	
	static void ResetField();
	static Paddle* GetLeftPaddle();
	static Paddle* GetRightPaddle();
	
private:
	static void Init();
	static void Kill();
	
	static bool m_isRunning;
	static std::vector<Screen*> m_screens;
};
