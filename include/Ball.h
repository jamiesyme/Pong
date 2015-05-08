#pragma once

#include "Entity.h"
#include <vector>


class Ball : public Entity {
public:
	Ball();
	~Ball();
	
	void Move(float delta); // UN-NEEDED: PUT INTO TICK()
	void Tick();
	void Draw();
	
	void SetStartingVelocity(int speed);
	int GetSpeed();
	int GetVelocityX();
	int GetVelocityY();
	void SetSpeed(int speed);
	void SetVelocityX(int x);
	void SetVelocityY(int y);

private:
	int m_vx;
	int m_vy;
	float m_smoothStartPadding;
	std::vector<int> m_ghostCoords;
	std::vector<float> m_ghostSpawnTimes;
};
