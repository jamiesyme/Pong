#include "UiButton.h"
#include "UiText.h"
#include "Window.h"
#include "Input.h"



UiButton::UiButton()
{
	m_x1 = 0;
	m_x2 = 0;
	m_y1 = 0;
	m_y2 = 0;
	m_isHovered = false;
	m_isDown = false;
	m_wasJustPressed = false;
	m_alpha = 1.0f;
	m_text = new UiText();
}



UiButton::~UiButton()
{
	delete m_text;
}



void UiButton::Tick()
{
	// Fix the hover
	int mx = Input::GetMouseX();
	int my = Input::GetMouseY();
	if (mx >= GetX1() && mx <= GetX2() && my >= GetY1() && my <= GetY2())
		m_isHovered = true;
	else
		m_isHovered = false;
		
	// Click the button
	m_wasJustPressed = false;
	if (m_isHovered && Input::WasMousePressed(SDL_BUTTON_LEFT)) {
		m_isDown = true;
		m_wasJustPressed = true;
	}
	if (Input::WasMouseReleased(SDL_BUTTON_LEFT))
		m_isDown = false;
}



void UiButton::Draw()
{
	// Draw the background
	Window::SetFillColor(1.0f, 1.0f, 1.0f, m_alpha);
	Window::FillRect(m_x1, m_x2, m_y1, m_y2);
	
	// Draw more background if hovered (or clicked)
	if (m_isHovered) {
		int buf = 4;
		if (m_isDown)
			buf = 6;
		Window::SetFillColor(0.0f, 0.0f, 0.0f, m_alpha);
		Window::FillRect(m_x1 + buf, m_x2 - buf, m_y1 + buf, m_y2 - buf);
	}
	
	// Draw the outline
	Window::SetFillColor(0.0f, 0.0f, 0.0f, m_alpha);
	Window::DrawRect(m_x1, m_x2, m_y1, m_y2, 3);
	
	// Draw the text
	if (m_isHovered)
		m_text->SetTextColor(255, 255, 255, 255);
	else
		m_text->SetTextColor(0, 0, 0, 255);
	m_text->SetCenterPosition((m_x1 + m_x2) / 2, (m_y1 + m_y2) / 2);
	m_text->SetTextColorA((int)(m_alpha * 255.0f));
	m_text->Draw();
}



bool UiButton::WasPressed()
{
	return m_wasJustPressed;
}



void UiButton::SetPosAndSize(int x1, int y1, int w, int h)
{
	m_x1 = x1;
	m_y1 = y1;
	m_x2 = x1 + w - 1;
	m_y2 = y1 + h - 1;
}



void UiButton::SetCoords(int x1, int x2, int y1, int y2)
{
	m_x1 = x1;
	m_x2 = x2;
	m_y1 = y1;
	m_y2 = y2;
}



void UiButton::SetX1(int x)
{
	m_x1 = x;
}



void UiButton::SetX2(int x)
{
	m_x2 = x;
}



void UiButton::SetY1(int y)
{
	m_y1 = y;
}



void UiButton::SetY2(int y)
{
	m_y2 = y;
}



int UiButton::GetX1()
{
	return m_x1;
}



int UiButton::GetX2()
{
	return m_x2;
}



int UiButton::GetY1()
{
	return m_y1;
}



int UiButton::GetY2()
{
	return m_y2;
}



int UiButton::GetWidth()
{
	return m_x2 - m_x1 + 1;
}



int UiButton::GetHeight()
{
	return m_y2 - m_y1 + 1;
}



void UiButton::SetAlpha(float alpha)
{
	m_alpha = alpha;
}



float UiButton::GetAlpha()
{
	return m_alpha;
}



void UiButton::SetText(std::string text, std::string fontFilename, int size)
{
	m_text->SetText(text);
	m_text->SetTextSize(size);
	m_text->SetFont(fontFilename);
}



UiText* UiButton::GetUiText()
{
	return m_text;
}
