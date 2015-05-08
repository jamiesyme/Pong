#include "Ball.h"
#include "Window.h"
#include "Clock.h"
#include <cstdlib>
#include <cmath>



Ball::Ball()
{
	m_vx = 0;
	m_vy = 0;
	m_smoothStartPadding = 0.0f;
	SetWidth(20);
	SetHeight(20);
}



Ball::~Ball()
{
}



void Ball::Move(float delta)
{
	// Apply smooth padding
	if (m_smoothStartPadding > 0.0f)
		delta *= (1.0f - m_smoothStartPadding);
	
	// Move the ball
	SetX1(GetX1() + (int)((float)GetVelocityX() * delta));
	SetY1(GetY1() + (int)((float)GetVelocityY() * delta));
}



void Ball::Tick()
{
	// Add a ghost if we're moving
	if (GetSpeed() > 0.0f)
	{
		m_ghostCoords.push_back(GetX1());
		m_ghostCoords.push_back(GetY1());
		m_ghostSpawnTimes.push_back(Clock::GetTime());
	}
	
	// Move the ball
	Move(Clock::GetDelta());
	
	// Limit the smooth padding
	if (m_smoothStartPadding > 0.0f)
		m_smoothStartPadding -= Clock::GetDelta();
}



void Ball::Draw()
{
	// Draw the ghosts
	for (int i = 0; i < m_ghostCoords.size(); i += 2)
	{
		// Get the info
		int x1 = m_ghostCoords[i + 0];
		int y1 = m_ghostCoords[i + 1];
		float alpha = (1.0f - (Clock::GetTime() - m_ghostSpawnTimes[i / 2])) - 0.75f;
		
		// Remove dead ghosts
		if (alpha < 0.0f)
		{
			m_ghostCoords.erase(m_ghostCoords.begin() + i);
			m_ghostCoords.erase(m_ghostCoords.begin() + i);
			m_ghostSpawnTimes.erase(m_ghostSpawnTimes.begin() + i / 2);
			i -= 2;
			continue;
		}
		
		// Draw the ghost
		Window::SetFillColor(0.1f, 0.1f, 0.1f, alpha);
		Window::FillRect(x1, x1 + GetWidth() - 1, y1, y1 + GetHeight() - 1);
	}
	
	// Draw the real ball
	Window::SetFillColor(0.1f, 0.1f, 0.1f);
	Window::FillRect(GetX1(), GetX2(), GetY1(), GetY2());
}



void Ball::SetStartingVelocity(int speed)
{
	// VelX: Atleast (-)0.5
	// VelY: Atleast (-)0.25, Less than (-)0.75
	float vx =  (float)rand() / (float)RAND_MAX;
	vx = (vx < 0.5f ? -0.5f - vx : vx);
	float vy = ((float)rand() / (float)RAND_MAX);
	vy = (vy < 0.5f ? -0.25 - vy : vy - 0.25f);
	
	// Normalize
	float mag = std::sqrt(vx * vx + vy * vy);
	vx /= mag;
	vy /= mag;
	
	// Set the velocity
	m_vx = (int)(vx * (float)speed);
	m_vy = (int)(vy * (float)speed);
	
	// Set the start padding
	m_smoothStartPadding = 1.0f;
}



int Ball::GetSpeed()
{
	float vx = (float)m_vx;
	float vy = (float)m_vy;
	return (int)std::sqrt(vx * vx + vy * vy);
}



int Ball::GetVelocityX()
{
	return m_vx;
}



int Ball::GetVelocityY()
{
	return m_vy;
}



void Ball::SetSpeed(int speed)
{
	// Normalize the velocity
	float vx = (float)m_vx;
	float vy = (float)m_vy;
	float mag = std::sqrt(vx * vx + vy * vy);
	if (mag != 0.0f)
	{
		vx /= mag;
		vy /= mag;
	}
	
	// Set the new velocity
	m_vx = (int)(vx * (float)speed);
	m_vy = (int)(vy * (float)speed);
}



void Ball::SetVelocityX(int x)
{
	m_vx = x;
}



void Ball::SetVelocityY(int y)
{
	m_vy = y;
}
