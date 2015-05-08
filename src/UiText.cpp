#include "UiText.h"
#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>



UiText::UiText()
{
	m_anchor = 1;
	m_posX = 0;
	m_posY = 0;
	m_sizeX = 0;
	m_sizeY = 0;
	m_textColorR = 0;
	m_textColorG = 0;
	m_textColorB = 0;
	m_textColorA = 255;
	m_textSize = 16;
	m_text = "Default Text";
	m_fontFilename = "";
	m_texture = 0;
}



UiText::~UiText()
{
	if (m_texture != 0)
		SDL_DestroyTexture(m_texture);
}



void UiText::Draw()
{
	if (m_texture == 0)
		return;
	SDL_Rect src = { 0, 0, GetSizeX(), GetSizeY() };
	SDL_Rect dst = { GetPositionX1(), GetPositionY1(), GetSizeX(), GetSizeY() };
	SDL_SetTextureColorMod(m_texture, GetTextColorR(), GetTextColorG(), GetTextColorB());
	SDL_SetTextureAlphaMod(m_texture, GetTextColorA());
	SDL_RenderCopy(Window::GetRenderer(), m_texture, &src, &dst);
}



void UiText::SetCenterPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = 5;
}



void UiText::SetTopLeftPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = 3;
}



void UiText::SetTopRightPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = 4;
}



void UiText::SetBottomLeftPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = 1;
}



void UiText::SetBottomRightPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
	m_anchor = 2;
}



void UiText::SetFont(std::string fontFilename)
{
	m_fontFilename = fontFilename;
	_reloadText();
}



void UiText::SetText(std::string text)
{
	m_text = text;
	_reloadText();
}



void UiText::SetTextSize(int point)
{
	m_textSize = point;
	_reloadText();
}



void UiText::SetTextColor(int r, int g, int b, int a)
{
	m_textColorR = r;
	m_textColorG = g;
	m_textColorB = b;
	m_textColorA = a;
}



void UiText::SetTextColorR(int r)
{
	m_textColorR = r;
}



void UiText::SetTextColorG(int g)
{
	m_textColorG = g;
}



void UiText::SetTextColorB(int b)
{
	m_textColorB = b;
}



void UiText::SetTextColorA(int a)
{
	m_textColorA = a;
}



int UiText::GetPositionX1() const
{
	if (m_anchor == 1 || m_anchor == 3)
		return m_posX;
	if (m_anchor == 2 || m_anchor == 4)
		return m_posX - GetSizeX() + 1;
	return m_posX - GetSizeX() / 2;
}



int UiText::GetPositionX2() const
{
	if (m_anchor == 1 || m_anchor == 3)
		return m_posX + GetSizeX() - 1;
	if (m_anchor == 2 || m_anchor == 4)
		return m_posX;
	return m_posX + GetSizeX() / 2;
}



int UiText::GetPositionY1() const
{
	if (m_anchor == 1 || m_anchor == 2)
		return m_posY;
	if (m_anchor == 3 || m_anchor == 4)
		return m_posY - GetSizeY() + 1;
	return m_posY - GetSizeY() / 2;
}



int UiText::GetPositionY2() const
{
	if (m_anchor == 1 || m_anchor == 2)
		return m_posY + GetSizeY() - 1;
	if (m_anchor == 3 || m_anchor == 4)
		return m_posY;
	return m_posY + GetSizeY() / 2;
}



int UiText::GetSizeX() const
{
	return m_sizeX;
}



int UiText::GetSizeY() const
{
	return m_sizeY;
}



int UiText::GetTextColorR() const
{
	return m_textColorR;
}



int UiText::GetTextColorG() const
{
	return m_textColorG;
}



int UiText::GetTextColorB() const
{
	return m_textColorB;
}



int UiText::GetTextColorA() const
{
	return m_textColorA;
}


int UiText::GetTextSize() const
{
	return m_textSize;
}



std::string UiText::GetText() const
{
	return m_text;
}



std::string UiText::GetFont() const
{
	return m_fontFilename;
}



void UiText::_reloadText()
{
	if (m_fontFilename.size() == 0)
		return;
	
	TTF_Font* font = TTF_OpenFont(m_fontFilename.c_str(), m_textSize);
	if (font == 0) {
		std::cout << "Font '" << m_fontFilename.c_str() << "' failed to load!" << std::endl;
		std::cout << "\t: " << TTF_GetError() << std::endl;
		return;
	}
		
	SDL_Color col = { 255, 255, 255, 255 };
	//col.r = GetTextColorR();
	//col.g = GetTextColorG();
	//col.b = GetTextColorB();
	//col.a = GetTextColorA();
	SDL_Surface* surf = TTF_RenderUTF8_Blended(font, m_text.c_str(), col);
	
	if (surf != 0) 
	{
		SDL_DestroyTexture(m_texture);
		m_texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), surf);
		SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
		
		m_sizeX = surf->w;
		m_sizeY = surf->h;
		
		SDL_FreeSurface(surf);	
	}
	
	TTF_CloseFont(font);
}
