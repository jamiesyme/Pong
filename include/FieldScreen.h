#pragma once

#include "Screen.h"
class Paddle;
class Ball;
class UiText;
class ParticleEmitter;


class FieldScreen : public Screen {
public:
	FieldScreen();
	~FieldScreen();
	
	void Tick();
	void Draw();
	
	void PointForLeft();
	void PointForRight();
	
	void ResetAll();
	void ResetScores();
	void ResetBall();
	
	Paddle* GetLeftPaddle();
	Paddle* GetRightPaddle();

private:
	Paddle* m_leftPaddle;
	Paddle* m_rightPaddle;
	Ball* m_ball;
	int m_leftScore;
	int m_rightScore;
	UiText* m_leftScoreText;
	UiText* m_rightScoreText;
	ParticleEmitter* m_emitter;
	
	void _SpawnParticles(float x, float y, float direction);
};
