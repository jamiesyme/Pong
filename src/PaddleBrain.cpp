#include "PaddleBrain.h"



PaddleBrain::PaddleBrain(Paddle* paddle, Ball* ball)
{
	m_paddle = paddle;
	m_ball = ball;
	m_type = BT_PLAYER_1;
}



PaddleBrain::~PaddleBrain()
{
}



Paddle* PaddleBrain::GetPaddle()
{
	return m_paddle;
}



Ball* PaddleBrain::GetBall()
{
	return m_ball;
}



void PaddleBrain::SetType(BrainType type)
{
	m_type = type;
}



PaddleBrain::BrainType PaddleBrain::GetType()
{
	return m_type;
}
