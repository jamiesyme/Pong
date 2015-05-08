#pragma once

#include "Screen.h"
class FadeTimer;
class UiText;
class UiButton;


class PauseScreen : public Screen {
public:
	PauseScreen();
	~PauseScreen();
	
	void Tick();
	void Draw();

private:
	FadeTimer* m_fadeTimer;
	UiText* m_titleText;
	UiButton* m_resumeBut;
	UiButton* m_resetBut;
	UiButton* m_settingsBut;
	UiButton* m_quitBut;
};
