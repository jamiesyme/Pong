#pragma once

#include "Entity.h"
class PaddleBrain;


class Paddle : public Entity {
public:
	Paddle();
	~Paddle();
	
	void Tick();
	void Draw();
	
	void SetNewBrain(PaddleBrain* brain);
	PaddleBrain* GetBrain();

private:
	PaddleBrain* m_brain;
};
