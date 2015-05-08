#include "ParticleEmitter.h"
#include "Clock.h"
#include "Window.h"
#include <cstdlib>
#include <cmath>



ParticleEmitter::ParticleEmitter()
{
}



ParticleEmitter::~ParticleEmitter()
{
}



void ParticleEmitter::Tick()
{
	// For every particle...
	float delta = Clock::GetDelta();
	for (unsigned int i = 0; i < m_particles.size(); i++)
	{
		// Get the particle
		Particle& part = m_particles[i];
		
		// Move the particle
		part.x += part.vx * delta;
		part.y += part.vy * delta;
		
		// Kill the particle a little
		part.lifeLeft -= delta;
		
		// Is the particle dead
		if (part.lifeLeft <= 0.0f)
		{
			m_particles.erase(m_particles.begin() + i--);
			continue;
		}
	}
}



void ParticleEmitter::Draw()
{
	// Draw every particle
	for (unsigned int i = 0; i < m_particles.size(); i++)
	{
		Particle& part = m_particles[i];
		Window::SetFillColor(0.0f, 0.0f, 0.0f, part.lifeLeft / part.lifeSpan);
		float hs = part.s / 2.0f; // Half Size
		Window::FillRect(part.x - hs, part.x + hs, part.y - hs, part.y + hs);
	}
}



void ParticleEmitter::Spawn(SpawnInstructions instructions)
{
	// Spawn each particle
	for (int i = 0; i < instructions.num; i++)
	{
		// Create the particle
		Particle part;
		part.x = instructions.px;
		part.y = instructions.py;
		part.s = instructions.size;
		
		// Set the velocity
		float deg = instructions.dir;
		deg += instructions.dirVary * ((float)rand() / (float)RAND_MAX * 2.0f - 1.0f);
		float speed = instructions.speed;
		speed += instructions.speedVary * ((float)rand() / (float)RAND_MAX * 2.0f - 1.0f);
		part.vx = (int)(std::cos(deg * 3.141592654f / 180.0f) * speed);
		part.vy = (int)(std::sin(deg * 3.141592654f / 180.0f) * speed);
		
		// Set the time
		part.lifeSpan = instructions.lifeSpan;
		part.lifeLeft = instructions.lifeSpan - instructions.lifeVary * (float)rand() / (float)RAND_MAX;
		
		// Save the particle
		m_particles.push_back(part);
	}	
}
