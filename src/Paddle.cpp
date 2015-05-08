#include "Paddle.h"
#include "PaddleBrain.h"
#include "Window.h"



Paddle::Paddle()
{
	m_brain = 0;
	SetWidth(20);
	SetHeight(100);
}



Paddle::~Paddle()
{
	delete m_brain;
}



void Paddle::Tick()
{
	if (m_brain != 0)
		m_brain->Tick();
}



void Paddle::Draw()
{
	Window::SetFillColor(0.1f, 0.1f, 0.1f);
	Window::FillRect(GetX1(), GetX2(), GetY1(), GetY2());
}



void Paddle::SetNewBrain(PaddleBrain* brain)
{
	delete m_brain;
	m_brain = brain;
}



PaddleBrain* Paddle::GetBrain()
{
	return m_brain;
}
