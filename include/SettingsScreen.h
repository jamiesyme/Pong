#pragma once

#include "Screen.h"
#include "PaddleBrain.h"
class FadeTimer;
class UiText;
class UiButton;
class Paddle;


class SettingsScreen : public Screen {
public:
	SettingsScreen();
	~SettingsScreen();
	
	void Tick();
	void Draw();

private:
	FadeTimer* m_alphaTimer;
	UiText* m_titleText;
	UiText* m_leftConText;
	UiText* m_rightConText;
	UiButton* m_backButton;
	UiButton* m_leftConButton;
	UiButton* m_rightConButton;
	
	void _changePaddleBrain(Paddle* paddle, UiButton* button);
	void _updateButtonText(UiButton* button, PaddleBrain::BrainType t);
};
