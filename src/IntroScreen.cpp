#include "IntroScreen.h"
#include "FadeTimer.h"
#include "UiText.h"
#include "Game.h"
#include "Window.h"



IntroScreen::IntroScreen()
{
	m_alphaTimer = new FadeTimer();
	m_alphaTimer->SetFadeIn(1.0f, 1.0f);
	m_alphaTimer->SetFadeOut(1.0f, 1.0f);
	m_alphaTimer->StartFadeIn(true);
	m_pongText = new UiText();
	m_pongText->SetFont("../res/font.ttf");
	m_pongText->SetTextSize(96);
	m_pongText->SetText("Pong.");
	m_pongText->SetTextColor(255, 255, 255, 255);
}



IntroScreen::~IntroScreen()
{
	delete m_alphaTimer;
	delete m_pongText;
}



void IntroScreen::Tick()
{
	if (m_alphaTimer->IsDoneFadingOut())
		Game::PopNewScreen();
}



void IntroScreen::Draw()
{
	// Get the width and height
	int w = Window::GetWidth();
	int h = Window::GetHeight();
	
	// Get the alpha fade
	float fadeAlpha = m_alphaTimer->GetAlpha();
	
	// Draw the backbround
	float bgAlpha = 1.0f;
	if (m_alphaTimer->IsFadingOut())
		bgAlpha = fadeAlpha;
	Window::SetFillColor(0.0f, 0.0f, 0.0f, bgAlpha);
	Window::FillRect(0, w, 0, h);
	
	// Draw the text
	m_pongText->SetCenterPosition(w / 2, h / 2);
	m_pongText->SetTextColorA((int)(fadeAlpha * 255.0f));
	m_pongText->Draw();
}
