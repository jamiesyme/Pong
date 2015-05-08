#pragma once

#include "PaddleBrain.h"


class AiPaddleBrain : public PaddleBrain {
public:
	AiPaddleBrain(Paddle* paddle, Ball* ball);
	~AiPaddleBrain();
	
	void Tick();

private:
	int m_lastKnownBallVelX;
	int m_lastKnownBallVelY;
	int m_destinationY;
	
	int _predictBallY(); //...when will it reach us
};
