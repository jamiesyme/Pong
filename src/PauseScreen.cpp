#include "PauseScreen.h"
#include "FadeTimer.h"
#include "UiText.h"
#include "UiButton.h"
#include "Window.h"
#include "Input.h"
#include "Game.h"
#include "SettingsScreen.h"
#include <SDL2/SDL.h>



PauseScreen::PauseScreen()
{
	m_fadeTimer = new FadeTimer();
	m_fadeTimer->SetFadeIn(0.0f, 0.4f);
	m_fadeTimer->SetFadeOut(0.0f, 0.4f);
	m_fadeTimer->StartFadeIn(false);
	m_titleText = new UiText();
	m_titleText->SetText("Pause Menu");
	m_titleText->SetTextSize(48);
	m_titleText->SetTextColor(0, 0, 0, 255);
	m_titleText->SetFont("../res/font.ttf");
	m_resumeBut = new UiButton();
	m_resumeBut->SetText("Resume", "../res/font.ttf", 32);
	m_resetBut = new UiButton();
	m_resetBut->SetText("Reset", "../res/font.ttf", 32);
	m_settingsBut = new UiButton();
	m_settingsBut->SetText("Settings", "../res/font.ttf", 32);
	m_quitBut = new UiButton();
	m_quitBut->SetText("Quit", "../res/font.ttf", 32);
}



PauseScreen::~PauseScreen()
{
	delete m_fadeTimer;
	delete m_titleText;
	delete m_resumeBut;
	delete m_resetBut;
	delete m_settingsBut;
	delete m_quitBut;
}



void PauseScreen::Tick()
{
	// Fade in
	if (m_fadeTimer->IsFadingIn())
		return;
	
	// Fade out
	if (m_fadeTimer->IsFadingOut())
		return;
		
	// Quit
	if (m_fadeTimer->IsDoneFadingOut()) {
		Game::PopNewScreen();
		return;
	}
	
	// Start the fading out
	if (Input::WasKeyPressed(SDL_SCANCODE_ESCAPE)) {
		m_fadeTimer->StartFadeOut();
		return;
	}
	
	// Update the resume button
	m_resumeBut->Tick();
	if (m_resumeBut->WasPressed()) {
		m_fadeTimer->StartFadeOut();
		return;
	}
	
	// Update the reset button
	m_resetBut->Tick();
	if (m_resetBut->WasPressed()) {
		Game::ResetField();
		m_fadeTimer->StartFadeOut();
		return;
	}
	
	// Update the settings button
	m_settingsBut->Tick();
	if (m_settingsBut->WasPressed())
	{
		Game::PushNewScreen(new SettingsScreen());
		return;
	}
	
	// Update the quit button
	m_quitBut->Tick();
	if (m_quitBut->WasPressed()) {
		Game::Quit();
	}
}



void PauseScreen::Draw()
{
	int x1 = 200;
	int x2 = 600;
	int y1 = 100;
	int y2 = 500;

	// Draw the background
	float bgAlpha = m_fadeTimer->GetAlpha();
	Window::SetFillColor(1.0f, 1.0f, 1.0f, bgAlpha);
	Window::FillRect(x1, x2, y1, y2);
	Window::SetFillColor(0.0f, 0.0f, 0.0f, bgAlpha);
	Window::DrawRect(x1, x2, y1, y2, 3);
	
	// Render the title
	m_titleText->SetBottomLeftPosition(x1 + 10, y1 + 10);
	m_titleText->SetTextColorA((int)(bgAlpha * 255.0f));
	m_titleText->Draw();
	
	// Draw the buttons
	int ySpc = 65;
	m_resumeBut->SetPosAndSize(x1 + 100, y1 + 100 + ySpc * 0, 200, 40);
	m_resumeBut->SetAlpha(bgAlpha);
	m_resumeBut->Draw();
	m_resetBut->SetPosAndSize(x1 + 100, y1 + 100 + ySpc * 1, 200, 40);
	m_resetBut->SetAlpha(bgAlpha);
	m_resetBut->Draw();
	m_settingsBut->SetPosAndSize(x1 + 100, y1 + 100 + ySpc * 2, 200, 40);
	m_settingsBut->SetAlpha(bgAlpha);
	m_settingsBut->Draw();
	m_quitBut->SetPosAndSize(x1 + 100, y1 + 100 + ySpc * 3, 200, 40);
	m_quitBut->SetAlpha(bgAlpha);
	m_quitBut->Draw();
}


