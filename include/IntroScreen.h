#pragma once

#include "Screen.h"
class FadeTimer;
class UiText;


class IntroScreen : public Screen {
public:
	IntroScreen();
	~IntroScreen();
	
	void Tick();
	void Draw();

private:
	FadeTimer* m_alphaTimer;
	UiText* m_pongText;
};
