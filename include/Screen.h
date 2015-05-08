#pragma once


class Screen {
public:
	Screen() {}
	virtual ~Screen() {}
	
	virtual void Tick() {}
	virtual void Draw() {}

private:
	
};
