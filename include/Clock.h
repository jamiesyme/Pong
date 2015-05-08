#pragma once


class Clock {
public:
	static void Tick();
	
	static float GetTime();
	static float GetDelta();

private:
	static unsigned int m_tick; // Current tick count
	static unsigned int m_oTick; // Old tick count
};
