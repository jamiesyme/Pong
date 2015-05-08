#pragma once

#include <SDL2/SDL.h>
#include <vector>


class Input {
public:
	static void Tick();
	static void PushEvent(SDL_Event& e);
	
	static bool IsKeyDown(int sdlKey);
	static bool WasKeyPressed(int sdlKey);
	static bool WasKeyReleased(int sdlKey);
	
	static int GetMouseX();
	static int GetMouseY();
	static bool IsMouseDown(int sdlButton);
	static bool WasMousePressed(int sdlButton);
	static bool WasMouseReleased(int sdlButton);

private:
	static std::vector<int> m_keysDown;
	static std::vector<int> m_keysPressed;
	static std::vector<int> m_keysReleased;
	static std::vector<int> m_butsDown;
	static std::vector<int> m_butsPressed;
	static std::vector<int> m_butsReleased;
	static int m_mouseX;
	static int m_mouseY;
};
