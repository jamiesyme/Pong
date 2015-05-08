#include "Window.h"

SDL_Window* Window::m_window = 0;
SDL_Renderer* Window::m_renderer = 0;



void Window::Init()
{
	// Create the sdl window and renderer
	m_window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	// Set up some stuff... I'm so descriptive!
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
}



void Window::Kill()
{
	// Destroy the sdl window and renderer
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}



void Window::Clear(float r, float g, float b)
{
	SetFillColor(r, g, b);
	SDL_RenderClear(m_renderer);
}



void Window::Flip()
{
	SDL_RenderPresent(m_renderer);
}



void Window::SetFillColor(float r, float g, float b, float a)
{
	SDL_SetRenderDrawColor(m_renderer, (int)(r * 255.0f), 
																		 (int)(g * 255.0f), 
																		 (int)(b * 255.0f), 
																		 (int)(a * 255.0f));
}



void Window::FillRect(int x1, int x2, int y1, int y2)
{
	SDL_Rect rect;
	rect.x = x1;
	rect.y = y1;
	rect.w = x2 - x1 + 1;
	rect.h = y2 - y1 + 1;
	SDL_RenderFillRect(m_renderer, &rect);
}



void Window::DrawRect(int x1, int x2, int y1, int y2, int w)
{
	FillRect(x1, x1 + w - 1, y1, y2); // Left
	FillRect(x1, x2, y1, y1 + w - 1); // Top
	FillRect(x1, x2, y2 - w + 1, y2); // Bottom
	FillRect(x2 - w + 1, x2, y1, y2); // Right
}



int Window::GetWidth()
{
	int w = 0;
	SDL_GetRendererOutputSize(m_renderer, &w, 0);
	return w;
}



int Window::GetHeight()
{
	int h = 0;
	SDL_GetRendererOutputSize(m_renderer, 0, &h);
	return h;
}



SDL_Renderer* Window::GetRenderer()
{
	return m_renderer;
}
