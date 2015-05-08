#include "Clock.h"
#include <SDL2/SDL.h>

unsigned int Clock::m_tick = 0;
unsigned int Clock::m_oTick = 0;



void Clock::Tick()
{
	m_oTick = m_tick;
	m_tick = SDL_GetTicks();
}



float Clock::GetTime()
{
	return (float)m_tick / 1000.0f;
}



float Clock::GetDelta()
{
	return (m_tick - m_oTick) / 1000.0f;
}
