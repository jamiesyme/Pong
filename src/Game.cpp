#include "Game.h"
#include "Screen.h"
#include "Clock.h"
#include "Window.h"
#include "Input.h"
#include "IntroScreen.h"
#include "FieldScreen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

bool Game::m_isRunning;
std::vector<Screen*> Game::m_screens;



void Game::Run()
{
	// Initialize the game
	Init();
	
	// Time for the main loop
	while (m_isRunning) 
	{
		// Update the clock
		Clock::Tick();
		
		// Update the top screen
		if (GetTopScreen() != 0)
			GetTopScreen()->Tick();
	
		// Draw all the screens (with the last being on top)
		Window::Clear(1.0f, 1.0f, 1.0f);
		for (unsigned int i = 0; i < m_screens.size(); i++)
			m_screens[i]->Draw();
		Window::Flip();
		
		// Update the Input before we check the events
		Input::Tick();
	
		// Check events so we can quit
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				m_isRunning = false;
			Input::PushEvent(e);
		}
	}
	
	// Close down the game
	Kill();
}



void Game::Quit()
{
	m_isRunning = false;
}



void Game::Init()
{
	// Initialize sdl
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	// Create the window
	Window::Init();
	
	// Create the title screen and field screen (game/field screen is always on the bottom)
	PushNewScreen(new FieldScreen());
	PushNewScreen(new IntroScreen());
	
	// We're running
	m_isRunning = true;
}



void Game::Kill()
{
	// Destroy any screens left
	for (unsigned int i = 0; i < m_screens.size(); i++)
		delete m_screens[i];
	m_screens.clear();

	// Destroy the window
	Window::Kill();
	
	// Quit sdl
	TTF_Quit();
	SDL_Quit();
}



void Game::PushNewScreen(Screen* screen)
{
	if (screen != 0)
		m_screens.push_back(screen);
}



void Game::PopNewScreen()
{
	if (m_screens.size() == 0)
		return;
	delete m_screens[m_screens.size() - 1];
	m_screens.erase(m_screens.end() - 1);
}



Screen* Game::GetTopScreen()
{
	if (m_screens.size() == 0)
		return 0;
	return m_screens[m_screens.size() - 1];
}



void Game::ResetField()
{
	if (m_screens.size() == 0)
		return;
	((FieldScreen*)m_screens[0])->ResetAll(); // Screen 0 is always the field.
}



Paddle* Game::GetLeftPaddle()
{
	if (m_screens.size() == 0)
		return 0;
	((FieldScreen*)m_screens[0])->GetLeftPaddle(); // Screen 0 is always the field.
}



Paddle* Game::GetRightPaddle()
{
	if (m_screens.size() == 0)
		return 0;
	((FieldScreen*)m_screens[0])->GetRightPaddle(); // Screen 0 is always the field.
}
