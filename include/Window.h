#pragma once

#include <SDL2/SDL.h>


class Window {
public:
	static void Init();
	static void Kill();
	
	static void Clear(float r, float g, float b);
	static void Flip();
	
	static void SetFillColor(float r, float g, float b, float a = 1.0f);
	static void FillRect(int x1, int x2, int y1, int y2);
	static void DrawRect(int x1, int x2, int y1, int y2, int w);
	
	static int GetWidth();
	static int GetHeight();
	
	static SDL_Renderer* GetRenderer();

private:
	static SDL_Window* m_window;
	static SDL_Renderer* m_renderer;
};
