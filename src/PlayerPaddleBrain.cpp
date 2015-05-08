#include "PlayerPaddleBrain.h"
#include "Paddle.h"
#include "Input.h"
#include "Clock.h"
#include "Window.h"



PlayerPaddleBrain::PlayerPaddleBrain(Paddle* paddle, Ball* ball) : PaddleBrain(paddle, ball)
{
	SetType(BT_PLAYER_1_2);
}



PlayerPaddleBrain::~PlayerPaddleBrain()
{
}



void PlayerPaddleBrain::Tick()
{
	int speed = (int)(600.0f * Clock::GetDelta());
	BrainType type = GetType();
	
	if ((type == BT_PLAYER_1 || type == BT_PLAYER_1_2) && Input::IsKeyDown(SDL_SCANCODE_W)) 
		_moveDown(speed);
	if ((type == BT_PLAYER_1 || type == BT_PLAYER_1_2) && Input::IsKeyDown(SDL_SCANCODE_S))
		_moveUp(speed);
	
	if ((type == BT_PLAYER_2 || type == BT_PLAYER_1_2) && Input::IsKeyDown(SDL_SCANCODE_UP)) 
		_moveDown(speed);
	if ((type == BT_PLAYER_2 || type == BT_PLAYER_1_2) && Input::IsKeyDown(SDL_SCANCODE_DOWN))
		_moveUp(speed);
}



void PlayerPaddleBrain::_moveUp(float amount)
{
	Paddle* paddle = GetPaddle();
	paddle->SetY1(paddle->GetY1() + amount);
	if (paddle->GetY2() > Window::GetHeight())
		paddle->SetY2(Window::GetHeight() - 1);
}



void PlayerPaddleBrain::_moveDown(float amount)
{
	Paddle* paddle = GetPaddle();
	paddle->SetY1(paddle->GetY1() - amount);
	if (paddle->GetY1() < 0)
		paddle->SetY1(0);
}
