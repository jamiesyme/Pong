#include "AiPaddleBrain.h"
#include "Paddle.h"
#include "Ball.h"
#include "Clock.h"
#include "Window.h"
#include <cstdlib>
#include <cmath>
#include <iostream>



AiPaddleBrain::AiPaddleBrain(Paddle* paddle, Ball* ball) : PaddleBrain(paddle, ball)
{
	m_lastKnownBallVelX = 0;
	m_lastKnownBallVelY = 0;
	m_destinationY = 0;
	
	SetType(BT_AI_HARD); // HARD BY DEFAULT
}



AiPaddleBrain::~AiPaddleBrain()
{
}



void AiPaddleBrain::Tick()
{
	// Did the ball velocity change
	if (m_lastKnownBallVelX != GetBall()->GetVelocityX() || 
			m_lastKnownBallVelY != GetBall()->GetVelocityY())
	{
		// Calculate the destination
		m_destinationY = _predictBallY();
		
		// Save the velocity
		m_lastKnownBallVelX = GetBall()->GetVelocityX();
		m_lastKnownBallVelY = GetBall()->GetVelocityY();
	}
	
	// Move towards our destination
	if (GetBall()->GetSpeed() != 0)
	{
		int speed = (int)(600.0f * Clock::GetDelta());
		Paddle* paddle = GetPaddle();
		if (m_destinationY < paddle->GetCenterY())
			paddle->SetY1(paddle->GetY1() - speed);
		if (m_destinationY > paddle->GetCenterY())
			paddle->SetY1(paddle->GetY1() + speed);
	}
		
	// Clamp our position
	if (GetPaddle()->GetY1() < 0)
		GetPaddle()->SetY1(0);
	if (GetPaddle()->GetY2() > Window::GetHeight())
		GetPaddle()->SetY2(Window::GetHeight() - 1);
}



int AiPaddleBrain::_predictBallY()
{
	float posXDiff = 0.0f;
	if (GetBall()->GetCenterX() < GetPaddle()->GetCenterX())
		posXDiff = (float)(GetPaddle()->GetX1() - GetBall()->GetX2());
	else
		posXDiff = (float)(GetPaddle()->GetX2() - GetBall()->GetX1());
	float moveY = posXDiff / (float)GetBall()->GetVelocityX() * GetBall()->GetVelocityY();
	return GetBall()->GetCenterY() + (int)moveY;
}
