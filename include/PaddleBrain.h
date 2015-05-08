#pragma once

class Paddle;
class Ball;


class PaddleBrain {
public:
	enum BrainType {
		BT__BEFORE = 0,
		BT_PLAYER_1,
		BT_PLAYER_2,
		BT_PLAYER_1_2,
		BT_AI_EASY,
		BT_AI_MEDIUM,
		BT_AI_HARD,
		BT__AFTER
	};

	PaddleBrain(Paddle* paddle, Ball* ball);
	virtual ~PaddleBrain();
	
	virtual void Tick() = 0;

	Paddle* GetPaddle();
	Ball* GetBall();
	
	virtual void SetType(BrainType type);
	BrainType GetType();

private:
	Paddle* m_paddle;
	Ball* m_ball;
	BrainType m_type;
};
