#include "Entity.h"



Entity::Entity()
{
	m_x = 0;
	m_y = 0;
	m_w = 100;
	m_h = 100;
}



Entity::~Entity()
{
}



void Entity::Tick()
{
}



void Entity::Draw()
{
}



void Entity::SetX1(int x)
{
	m_x = x;
}



void Entity::SetY1(int y)
{
	m_y = y;
}



void Entity::SetX2(int x)
{
	m_x = x - m_w + 1;
}



void Entity::SetY2(int y)
{
	m_y = y - m_h + 1;
}



void Entity::SetWidth(int w)
{
	m_w = w;
}



void Entity::SetHeight(int h)
{
	m_h = h;
}



void Entity::SetCenterX(int x)
{
	m_x = x - m_w / 2;
}



void Entity::SetCenterY(int y)
{
	m_y = y - m_h / 2;
}



int Entity::GetWidth()
{
	return m_w;
}



int Entity::GetHeight()
{
	return m_h;
}



int Entity::GetX1()
{
	return m_x;
}



int Entity::GetX2()
{
	return m_x + m_w - 1;
}



int Entity::GetY1()
{
	return m_y;
}



int Entity::GetY2()
{
	return m_y + m_h - 1;
}



int Entity::GetCenterX()
{
	return m_x + m_w / 2;
}



int Entity::GetCenterY()
{
	return m_y + m_h / 2;
}
