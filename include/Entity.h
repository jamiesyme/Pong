#pragma once


class Entity {
public:
	Entity();
	virtual ~Entity();
	
	virtual void Tick();
	virtual void Draw();
	
	void SetX1(int x);
	void SetY1(int y);
	void SetX2(int x);
	void SetY2(int y);
	void SetCenterX(int x);
	void SetCenterY(int y);
	void SetWidth(int w);
	void SetHeight(int h);
	int GetWidth();
	int GetHeight();
	int GetX1();
	int GetX2();
	int GetY1();
	int GetY2();
	int GetCenterX();
	int GetCenterY();

private:
	int m_x;
	int m_y;
	int m_w;
	int m_h;
};
