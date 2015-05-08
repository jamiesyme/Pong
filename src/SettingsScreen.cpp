#include "SettingsScreen.h"
#include "FadeTimer.h"
#include "UiText.h"
#include "UiButton.h"
#include "Paddle.h"
#include "PaddleBrain.h"
#include "AiPaddleBrain.h"
#include "PlayerPaddleBrain.h"
#include "Input.h"
#include "Window.h"
#include "Game.h"
#include <SDL2/SDL.h>



SettingsScreen::SettingsScreen()
{
	m_alphaTimer = new FadeTimer();
	m_alphaTimer->SetFadeIn(0.0f, 0.5f);
	m_alphaTimer->SetFadeOut(0.0f, 0.5f);
	m_alphaTimer->StartFadeIn(false);
	m_titleText = new UiText();
	m_titleText->SetText("Settings");
	m_titleText->SetTextSize(48);
	m_titleText->SetTextColor(0, 0, 0, 255);
	m_titleText->SetFont("../res/font.ttf");
	m_leftConText = new UiText();
	m_leftConText->SetText("Left Controller");
	m_leftConText->SetTextSize(32);
	m_leftConText->SetTextColor(0, 0, 0, 255);
	m_leftConText->SetFont("../res/font.ttf");
	m_rightConText = new UiText();
	m_rightConText->SetText("Right Controller");
	m_rightConText->SetTextSize(32);
	m_rightConText->SetTextColor(0, 0, 0, 255);
	m_rightConText->SetFont("../res/font.ttf");
	m_backButton = new UiButton();
	m_backButton->SetText("Back", "../res/font.ttf", 32);
	m_leftConButton = new UiButton();
	m_leftConButton->SetText("Null", "../res/font.ttf", 24);
	m_rightConButton = new UiButton();
	m_rightConButton->SetText("Null", "../res/font.ttf", 24);
	
	_updateButtonText(m_leftConButton, Game::GetLeftPaddle()->GetBrain()->GetType());
	_updateButtonText(m_rightConButton, Game::GetRightPaddle()->GetBrain()->GetType());
}



SettingsScreen::~SettingsScreen()
{
	delete m_alphaTimer;
	delete m_titleText;
	delete m_leftConText;
	delete m_rightConText;
	delete m_backButton;
	delete m_leftConButton;
	delete m_rightConButton;
}



void SettingsScreen::Tick()
{
	// If we are fading, don't try anything
	if (m_alphaTimer->IsFadingIn())
		return;
	if (m_alphaTimer->IsFadingOut())
		return;

	// Exit the settings when the user presses Escape
	if (Input::WasKeyPressed(SDL_SCANCODE_ESCAPE))
		m_alphaTimer->StartFadeOut();
	
	// Exit the settings when the user presses the "Back" button
	m_backButton->Tick();
	if (m_backButton->WasPressed())
		m_alphaTimer->StartFadeOut();
	
	// Destroy this screen if we have faded out
	if (m_alphaTimer->IsDoneFadingOut())
	{
		Game::PopNewScreen();
		return;
	}
	
	// Change the paddle brains (with the controller buttons)
	m_leftConButton->Tick();
	if (m_leftConButton->WasPressed())
		_changePaddleBrain(Game::GetLeftPaddle(), m_leftConButton);
	
	m_rightConButton->Tick();
	if (m_rightConButton->WasPressed())
		_changePaddleBrain(Game::GetRightPaddle(), m_rightConButton);
}



void SettingsScreen::Draw()
{
	int x1 = 100;
	int x2 = 700;
	int y1 = 75;
	int y2 = 525;
	
	// Draw the background
	float bgAlpha = m_alphaTimer->GetAlpha();
	Window::SetFillColor(1.0f, 1.0f, 1.0f, bgAlpha);
	Window::FillRect(x1, x2, y1, y2);
	Window::SetFillColor(0.0f, 0.0f, 0.0f, bgAlpha);
	Window::DrawRect(x1, x2, y1, y2, 3);
	
	// Render the title
	m_titleText->SetBottomLeftPosition(x1 + 10, y1 + 10);
	m_titleText->SetTextColorA((int)(bgAlpha * 255.0f));
	m_titleText->Draw();
	
	// Render the back button
	m_backButton->SetPosAndSize(x2 - 150 - 11, y1 + 10, 150, 50);
	m_backButton->SetAlpha(bgAlpha);
	m_backButton->Draw();
	
	// Render the controllers' text
	m_leftConText->SetCenterPosition(x1 + (x2 - x1 + 1) / 4, y1 + 100);
	m_leftConText->SetTextColorA((int)(bgAlpha * 255.0f));
	m_leftConText->Draw();
	m_rightConText->SetCenterPosition(x1 + (x2 - x1 + 1) / 4 * 3, y1 + 100);
	m_rightConText->SetTextColorA((int)(bgAlpha * 255.0f));
	m_rightConText->Draw();
	
	// Render the controllers' buttons
	m_leftConButton->SetPosAndSize((m_leftConText->GetPositionX1() + m_leftConText->GetPositionX2()) / 2 - 75, 
																 m_leftConText->GetPositionY2() + 10, 150, 40);
	m_leftConButton->SetAlpha(bgAlpha);
	m_leftConButton->Draw();
	m_rightConButton->SetPosAndSize((m_rightConText->GetPositionX1() + m_rightConText->GetPositionX2()) / 2 - 75, 
																	m_rightConText->GetPositionY2() + 10, 150, 40);
	m_rightConButton->SetAlpha(bgAlpha);
	m_rightConButton->Draw();
}



void SettingsScreen::_changePaddleBrain(Paddle* paddle, UiButton* button)
{
	// Get the old brain
	PaddleBrain* oldBrain = paddle->GetBrain();
	
	// Calculate the new type
	PaddleBrain::BrainType newType = (PaddleBrain::BrainType)(oldBrain->GetType() + 1);
	if (newType == PaddleBrain::BT__AFTER)
		newType = (PaddleBrain::BrainType)(PaddleBrain::BT__BEFORE + 1);
	
	// Create the new brain
	PaddleBrain* newBrain = 0;
	switch (newType)
	{
	case PaddleBrain::BT_PLAYER_1:
		newBrain = new PlayerPaddleBrain(oldBrain->GetPaddle(), oldBrain->GetBall());
		break;
	case PaddleBrain::BT_PLAYER_2:
		newBrain = new PlayerPaddleBrain(oldBrain->GetPaddle(), oldBrain->GetBall());
		break;
	case PaddleBrain::BT_PLAYER_1_2:
		newBrain = new PlayerPaddleBrain(oldBrain->GetPaddle(), oldBrain->GetBall());
		break;
	case PaddleBrain::BT_AI_EASY:
		newBrain = new AiPaddleBrain(oldBrain->GetPaddle(), oldBrain->GetBall());
		break;
	case PaddleBrain::BT_AI_MEDIUM:
		newBrain = new AiPaddleBrain(oldBrain->GetPaddle(), oldBrain->GetBall());
		break;
	case PaddleBrain::BT_AI_HARD:
		newBrain = new AiPaddleBrain(oldBrain->GetPaddle(), oldBrain->GetBall());
		break;
	};
	
	// Use the new brain
	newBrain->SetType(newType); // TEMPORARY cause there is no difference between the AI's
	paddle->SetNewBrain(newBrain);
	
	// Update the button
	_updateButtonText(button, newType);
}



void SettingsScreen::_updateButtonText(UiButton* button, PaddleBrain::BrainType t)
{
	switch (t)
	{
	case PaddleBrain::BT_PLAYER_1:
		button->GetUiText()->SetText("Player 1");
		break;
	case PaddleBrain::BT_PLAYER_2:
		button->GetUiText()->SetText("Player 2");
		break;
	case PaddleBrain::BT_PLAYER_1_2:
		button->GetUiText()->SetText("Player 1/2");
		break;
	case PaddleBrain::BT_AI_EASY:
		button->GetUiText()->SetText("Ai (Easy)");
		break;
	case PaddleBrain::BT_AI_MEDIUM:
		button->GetUiText()->SetText("Ai (Medium)");
		break;
	case PaddleBrain::BT_AI_HARD:
		button->GetUiText()->SetText("Ai (Hard)");
		break;
	};
}
