#include "FieldScreen.h"
#include "UiText.h"
#include "ParticleEmitter.h"
#include "PauseScreen.h"
#include "Paddle.h"
#include "PlayerPaddleBrain.h"
#include "AiPaddleBrain.h"
#include "Ball.h"
#include "Input.h"
#include "Window.h"
#include "Clock.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <sstream>
#include <iostream>



FieldScreen::FieldScreen()
{
	// Create the ball
	m_ball = new Ball();
	m_ball->SetCenterX(Window::GetWidth() / 2);
	m_ball->SetCenterY(Window::GetHeight() / 2);

	// Create the paddles
	m_leftPaddle = new Paddle();
	m_leftPaddle->SetNewBrain(new PlayerPaddleBrain(m_leftPaddle, m_ball)); // PLAYER
	//m_leftPaddle->SetNewBrain(new AiPaddleBrain(m_leftPaddle, m_ball));   // AI
	m_leftPaddle->SetCenterX(50);
	m_leftPaddle->SetCenterY(Window::GetHeight() / 2);
	m_rightPaddle = new Paddle();
	m_rightPaddle->SetNewBrain(new AiPaddleBrain(m_rightPaddle, m_ball));
	m_rightPaddle->SetCenterX(750);
	m_rightPaddle->SetCenterY(Window::GetHeight() / 2);
	
	// Create the texts
	m_leftScoreText = new UiText();
	m_leftScoreText->SetFont("../res/font_bold.ttf");
	m_leftScoreText->SetTextSize(32);
	m_leftScoreText->SetTextColor(0, 0, 0, 128);
	m_rightScoreText = new UiText();
	m_rightScoreText->SetFont("../res/font_bold.ttf");
	m_rightScoreText->SetTextSize(32);
	m_rightScoreText->SetTextColor(0, 0, 0, 128);
	
	// Set the scores
	ResetScores();
	
	// Create the particle emitter
	m_emitter = new ParticleEmitter();
	
}



FieldScreen::~FieldScreen()
{
	delete m_ball;
	delete m_leftPaddle;
	delete m_rightPaddle;
	delete m_leftScoreText;
	delete m_rightScoreText;
	delete m_emitter;
}



void FieldScreen::Tick()
{
	// Pause the game
	if (Input::WasKeyPressed(SDL_SCANCODE_ESCAPE)) 
	{
		Game::PushNewScreen(new PauseScreen());
		return;
	}

	// Update the ball (and save some stats)
	int obx1 = m_ball->GetX1();
	int oby1 = m_ball->GetY1();
	int obx2 = m_ball->GetX2();
	int oby2 = m_ball->GetY2(); 
	m_ball->Tick();
	int nbx1 = m_ball->GetX1();
	int nby1 = m_ball->GetY1();
	int nbx2 = m_ball->GetX2();
	int nby2 = m_ball->GetY2();

	// Update the paddles
	m_leftPaddle->Tick();
	m_rightPaddle->Tick();
	
	// Update the particle emitter
	m_emitter->Tick();
	
	// Launch the ball (DEBUG: or reset it)
	if (Input::WasKeyPressed(SDL_SCANCODE_SPACE))
	{
		if (m_ball->GetSpeed() == 0) {
			m_ball->SetStartingVelocity(800);
		}else
			ResetBall();
	}
	
	// Points!
	//	-	On left
	if (m_ball->GetX1() < 0 && m_ball->GetVelocityX() < 0)
	{
		_SpawnParticles((float)m_ball->GetX1(), (float)m_ball->GetCenterY(), 0.0f);
		ResetBall();
		PointForRight();
	}
	// 	- On right
	if (m_ball->GetX2() > Window::GetWidth() && m_ball->GetVelocityX() > 0)
	{
		_SpawnParticles((float)m_ball->GetX2(), (float)m_ball->GetCenterY(), 180.0f);
		ResetBall();
		PointForLeft();
	}
		
		
	// Bounce the ball off the walls
	//	-	Bottom
	if (m_ball->GetY1() < 0 && m_ball->GetVelocityY() < 0)
	{
		m_ball->SetY1(-m_ball->GetY1());
		m_ball->SetVelocityY(-m_ball->GetVelocityY());
		_SpawnParticles((float)m_ball->GetCenterX(), (float)m_ball->GetY1(), 90.0f);
	}
	// 	- Top
	if (m_ball->GetY2() >= Window::GetHeight() && m_ball->GetVelocityY() > 0)
	{
		m_ball->SetY2(Window::GetHeight() - (m_ball->GetY2() - Window::GetHeight()) - 1);
		m_ball->SetVelocityY(-m_ball->GetVelocityY());
		_SpawnParticles((float)m_ball->GetCenterX(), (float)m_ball->GetY2(), 270.0f);
	}
	
	
	// Check left paddle
	if (m_ball->GetVelocityX() < 0 &&
			obx1 > m_leftPaddle->GetX2() &&
			nbx1 <= m_leftPaddle->GetX2() &&
			nby1 <= m_leftPaddle->GetY2() &&
			nby2 >= m_leftPaddle->GetY1())
	{		// THE RIGHT SIDE
		m_ball->SetX1(m_leftPaddle->GetX2() + (m_leftPaddle->GetX2() - m_ball->GetX1()) + 1);
		m_ball->SetVelocityX(-m_ball->GetVelocityX());
		m_ball->SetSpeed(m_ball->GetSpeed() + 20);
		_SpawnParticles((float)m_leftPaddle->GetX2(), (float)m_ball->GetCenterY(), 0.0f);
	} else
	if (m_ball->GetVelocityY() < 0 &&
			oby1 > m_leftPaddle->GetY2() &&
			nby1 <= m_leftPaddle->GetY2() &&
			nbx1 <= m_leftPaddle->GetX2() &&
			nbx2 >= m_leftPaddle->GetX1())
	{		// THE TOP SIDE
		m_ball->SetY1(m_leftPaddle->GetY2() + (m_leftPaddle->GetY2() - m_ball->GetY1()) + 1);
		m_ball->SetVelocityY(-m_ball->GetVelocityY());
		_SpawnParticles((float)m_ball->GetCenterX(), (float)m_leftPaddle->GetY2(), 90.0f);
	} else
	if (m_ball->GetVelocityY() > 0 &&
			oby2 < m_leftPaddle->GetY1() &&
			nby2 >= m_leftPaddle->GetY1() &&
			nbx1 <= m_leftPaddle->GetX2() &&
			nbx2 >= m_leftPaddle->GetX1())
	{		// THE BOTTOM SIDE
		m_ball->SetY2(m_leftPaddle->GetY1() - (m_ball->GetY2() - m_leftPaddle->GetY1()) - 1);
		m_ball->SetVelocityY(-m_ball->GetVelocityY());
		_SpawnParticles((float)m_ball->GetCenterX(), (float)m_leftPaddle->GetY1(), 270.0f);
	}
	
	
	// Check right paddle
	if (m_ball->GetVelocityX() > 0 &&
			obx2 < m_rightPaddle->GetX1() &&
			nbx2 >= m_rightPaddle->GetX1() &&
			nby1 <= m_rightPaddle->GetY2() &&
			nby2 >= m_rightPaddle->GetY1())
	{		// THE LEFT SIDE
		m_ball->SetX2(m_rightPaddle->GetX1() - (m_ball->GetX2() - m_rightPaddle->GetX1()) - 1);
		m_ball->SetVelocityX(-m_ball->GetVelocityX());
		m_ball->SetSpeed(m_ball->GetSpeed() + 20);
		_SpawnParticles((float)m_rightPaddle->GetX1(), (float)m_ball->GetCenterY(), 180.0f);
	} else
	if (m_ball->GetVelocityY() < 0 &&
			oby1 > m_rightPaddle->GetY2() &&
			nby1 <= m_rightPaddle->GetY2() &&
			nbx1 <= m_rightPaddle->GetX2() &&
			nbx2 >= m_rightPaddle->GetX1())
	{		// THE TOP SIDE
		m_ball->SetY1(m_rightPaddle->GetY2() + (m_rightPaddle->GetY2() - m_ball->GetY1()) + 1);
		m_ball->SetVelocityY(-m_ball->GetVelocityY());
		_SpawnParticles((float)m_ball->GetCenterX(), (float)m_rightPaddle->GetY2(), 90.0f);
	} else
	if (m_ball->GetVelocityY() > 0 &&
			oby2 < m_rightPaddle->GetY1() &&
			nby2 >= m_rightPaddle->GetY1() &&
			nbx1 <= m_rightPaddle->GetX2() &&
			nbx2 >= m_rightPaddle->GetX1())
	{		// THE BOTTOM SIDE
		m_ball->SetY2(m_rightPaddle->GetY1() - (m_ball->GetY2() - m_rightPaddle->GetY1()) - 1);
		m_ball->SetVelocityY(-m_ball->GetVelocityY());
		_SpawnParticles((float)m_ball->GetCenterX(), (float)m_rightPaddle->GetY1(), 270.0f);
	}
}



void FieldScreen::Draw()
{
	// Draw the scores
	int midX = Window::GetWidth() / 2;
	m_leftScoreText->SetBottomRightPosition(midX - 10, 10);
	m_leftScoreText->Draw();
	m_rightScoreText->SetBottomLeftPosition(midX + 10, 10);
	m_rightScoreText->Draw(); 

	// Draw the particle emitter
	m_emitter->Draw();

	// Draw the paddles and the ball
	m_leftPaddle->Draw();
	m_rightPaddle->Draw();
	m_ball->Draw();
}



void FieldScreen::PointForLeft()
{
	m_leftScore++;
	std::stringstream ss;
	ss << m_leftScore;
	m_leftScoreText->SetText(ss.str());
}



void FieldScreen::PointForRight()
{
	m_rightScore++;
	std::stringstream ss;
	ss << m_rightScore;
	m_rightScoreText->SetText(ss.str());
}



void FieldScreen::ResetAll()
{
	ResetScores();
	ResetBall();
	m_leftPaddle->SetCenterY(Window::GetHeight() / 2);
	m_rightPaddle->SetCenterY(Window::GetHeight() / 2);
}



void FieldScreen::ResetScores()
{
	m_leftScore = 0;
	m_rightScore = 0;
	m_leftScoreText->SetText("0");
	m_rightScoreText->SetText("0");
}



void FieldScreen::ResetBall()
{
	m_ball->SetSpeed(0);
	m_ball->SetCenterX(Window::GetWidth() / 2);
	m_ball->SetCenterY(Window::GetHeight() / 2);
}



Paddle* FieldScreen::GetLeftPaddle()
{
	return m_leftPaddle;
}



Paddle* FieldScreen::GetRightPaddle()
{
	return m_rightPaddle;
}



void FieldScreen::_SpawnParticles(float x, float y, float direction)
{
	ParticleEmitter::SpawnInstructions spawn;
	spawn.px = x;	
	spawn.py = y;
	spawn.size = 10.0f;			
	spawn.speed = 150.0f; 	
	spawn.speedVary = 100.0f;
	spawn.dir = direction; 		
	spawn.dirVary = 90.0f;
	spawn.lifeSpan = 0.25f; 
	spawn.lifeVary = 0.1f;
	spawn.num = 15;
	m_emitter->Spawn(spawn);
}
