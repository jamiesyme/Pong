#pragma once

#include <string>
class UiText;


class UiButton {
public:
	UiButton();
	~UiButton();
	
	void Tick();
	void Draw();
	
	bool WasPressed();
	
	void SetPosAndSize(int x1, int y1, int w, int h);
	void SetCoords(int x1, int x2, int y1, int y2);
	void SetX1(int x);
	void SetX2(int x);
	void SetY1(int y);
	void SetY2(int y);
	int GetX1();
	int GetX2();
	int GetY1();
	int GetY2();
	int GetWidth();
	int GetHeight();
	
	void SetAlpha(float alpha);
	float GetAlpha();
	
	void SetText(std::string text, std::string fontFilename, int size);
	UiText* GetUiText();

private:
	int m_x1;
	int m_x2;
	int m_y1;
	int m_y2;
	bool m_isHovered;
	bool m_isDown;
	bool m_wasJustPressed;
	float m_alpha;
	UiText* m_text;
};
