#pragma once

#include "PaddleBrain.h"


class PlayerPaddleBrain : public PaddleBrain {
public:
	PlayerPaddleBrain(Paddle* paddle, Ball* ball);
	~PlayerPaddleBrain();
	
	void Tick();

private:
	void _moveUp(float amount);
	void _moveDown(float amount);
};
