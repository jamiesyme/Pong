#include "Input.h"

#include <iostream>

std::vector<int> Input::m_keysDown;
std::vector<int> Input::m_keysPressed;
std::vector<int> Input::m_keysReleased;
std::vector<int> Input::m_butsDown;
std::vector<int> Input::m_butsPressed;
std::vector<int> Input::m_butsReleased;
int Input::m_mouseX;
int Input::m_mouseY;



void Input::Tick()
{
	m_keysPressed.clear();
	m_keysReleased.clear();
	m_butsPressed.clear();
	m_butsReleased.clear();
}



void Input::PushEvent(SDL_Event& e)
{
	// Key Down Event
	if (e.type == SDL_KEYDOWN) 
	{
		// Get the key and add it to "Keys Pressed"
		int key = e.key.keysym.scancode;
		m_keysPressed.push_back(key);
		
		// Add the key to the "Keys Down", but check first
		//   to see if it is already there.
		for (unsigned int i = 0; i <= m_keysDown.size(); i++)
		{
			if (i == m_keysDown.size())
			{
				m_keysDown.push_back(key);
				break;
			} else if (m_keysDown[i] == key)
				break;
		}
	}
	
	// Key Up Event
	if (e.type == SDL_KEYUP)
	{
		// Get the key and add it to "Keys Released"
		int key = e.key.keysym.scancode;
		m_keysReleased.push_back(key);
		
		// Remove the key from "Keys Down"
		for (int i = 0; i < (int)m_keysDown.size(); i++)
			if (m_keysDown[i] == key)
				m_keysDown.erase(m_keysDown.begin() + i--);
	}
	
	// Button Down Event
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		// Get the button and add it to "Buttons Pressed"
		int button = e.button.button;
		m_butsPressed.push_back(button);
		
		// Add the button to the "Buttons Down", but check 
		//   first to see if it is already there.
		for (unsigned int i = 0; i <= m_butsDown.size(); i++)
		{
			if (i == m_butsDown.size())
			{
				m_butsDown.push_back(button);
				break;
			} else if (m_butsDown[i] == button)
				break;
		}
	}
	
	// Button Up Event
	if (e.type == SDL_MOUSEBUTTONUP)
	{
		// Get the button and add it to "Buttons Released"
		int button = e.button.button;
		m_butsReleased.push_back(button);
		
		// Remove the button from "Buttons Down"
		for (int i = 0; i < (int)m_butsDown.size(); i++)
			if (m_butsDown[i] == button)
				m_butsDown.erase(m_butsDown.begin() + i--);
	}
	
	// Mouse movement
	if (e.type == SDL_MOUSEMOTION)
	{
		m_mouseX = e.motion.x;
		m_mouseY = e.motion.y;
	}
}



bool Input::IsKeyDown(int sdlKey)
{
	for (unsigned int i = 0; i < m_keysDown.size(); i++)
		if (m_keysDown[i] == sdlKey)
			return true;
	return false;
}



bool Input::WasKeyPressed(int sdlKey)
{
	for (unsigned int i = 0; i < m_keysPressed.size(); i++)
		if (m_keysPressed[i] == sdlKey)
			return true;
	return false;
}



bool Input::WasKeyReleased(int sdlKey)
{
	for (unsigned int i = 0; i < m_keysReleased.size(); i++)
		if (m_keysReleased[i] == sdlKey)
			return true;
	return false;
}



bool Input::IsMouseDown(int sdlButton)
{
	for (unsigned int i = 0; i < m_butsDown.size(); i++)
		if (m_butsDown[i] == sdlButton)
			return true;
	return false;
}



bool Input::WasMousePressed(int sdlButton)
{
	for (unsigned int i = 0; i < m_butsPressed.size(); i++)
		if (m_butsPressed[i] == sdlButton)
			return true;
	return false;
}



bool Input::WasMouseReleased(int sdlButton)
{
	for (unsigned int i = 0; i < m_butsReleased.size(); i++)
		if (m_butsReleased[i] == sdlButton)
			return true;
	return false;
}



int Input::GetMouseX()
{
	return m_mouseX;
}



int Input::GetMouseY()
{
	return m_mouseY;
}
