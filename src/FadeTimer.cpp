#include "FadeTimer.h"
#include "Clock.h"



FadeTimer::FadeTimer()
{
	m_inStartTime = -1.0f;
	m_inWaitFor = 0.0f;
	m_inFadeFor = 0.0f;
	m_outStartTime = -1.0f;
	m_outWaitFor = 0.0f;
	m_outFadeFor = 0.0f;
	m_alphaMin = 0.0f;
	m_alphaMax = 1.0f;
}



FadeTimer::~FadeTimer()
{
}



void FadeTimer::SetFadeIn(float waitFor, float fadeFor)
{
	m_inWaitFor = waitFor;
	m_inFadeFor = fadeFor;
}



void FadeTimer::SetFadeOut(float waitFor, float fadeFor)
{
	m_outWaitFor = waitFor;
	m_outFadeFor = fadeFor;
}



float FadeTimer::GetFadeInStartTime()
{
	return m_inStartTime;
}



float FadeTimer::GetFadeInEndTime()
{
	if (m_inStartTime < 0.0f)
		return -1.0f;
	return m_inStartTime + m_inWaitFor + m_inFadeFor;
}



float FadeTimer::GetFadeOutStartTime()
{
	return m_outStartTime;
}



float FadeTimer::GetFadeOutEndTime()
{
	if (m_outStartTime < 0.0f)
		return -1.0f;
	return m_outStartTime + m_outWaitFor + m_outFadeFor;
}



void FadeTimer::StartFadeIn(bool fadeOutAfter)
{
	m_inStartTime = Clock::GetTime();
	if (fadeOutAfter)
		m_outStartTime = GetFadeInEndTime();
}



void FadeTimer::StartFadeOut()
{
	m_inStartTime = 0.0f;
	m_outStartTime = Clock::GetTime();
}



void FadeTimer::SetAlphaMin(float min)
{
	m_alphaMin = min;
}



void FadeTimer::SetAlphaMax(float max)
{
	m_alphaMax = max;
}



float FadeTimer::GetAlpha()
{
	// If we haven't started fading in
	if (m_inStartTime < 0.0f)
		return m_alphaMin;
		
	// If we are currently fading in
	if (IsFadingIn())
	{
		float timePassed = Clock::GetTime() - m_inStartTime;
		if (timePassed <= m_inWaitFor)
			return m_alphaMin;
		else
			return m_alphaMin + (m_alphaMax - m_alphaMin) * ((timePassed - m_inWaitFor) / m_inFadeFor);
	}
	
	// If we've faded in, but haven't started fading out
	if (m_outStartTime < 0.0f)
		return m_alphaMax;
		
	// If we are currently fading out
	if (IsFadingOut())
	{
		float timePassed = Clock::GetTime() - m_outStartTime;
		if (timePassed <= m_outWaitFor)
			return m_alphaMax;
		else
			return m_alphaMax - (m_alphaMax - m_alphaMin) * ((timePassed - m_outWaitFor) / m_outFadeFor);
	}
	
	// We've finished fading out
	return m_alphaMin;
}



bool FadeTimer::IsFadingIn()
{
	if (GetFadeInStartTime() < 0.0f)	// Has the start time been set?
		return false;
	if (GetFadeInStartTime() > Clock::GetTime())		// Have we starting fading yet?
		return false;
	if (GetFadeInEndTime()   < Clock::GetTime())		// Have we finished fading yet?
		return false;
	return true;
}



bool FadeTimer::IsFadingOut()
{
	if (GetFadeOutStartTime() < 0.0f)	// Has the start time been set?
		return false;
	if (GetFadeOutStartTime() > Clock::GetTime())		// Have we starting fading yet?
		return false;
	if (GetFadeOutEndTime()   < Clock::GetTime())		// Have we finished fading yet?
		return false;
	return true;
}



bool FadeTimer::IsDoneFadingIn()
{
	if (GetFadeInStartTime() < 0.0f)	// Has the start time been set?
		return false;
	if (GetFadeInEndTime() >= Clock::GetTime())		// Is the end time still to come?
		return false;
	return true;
}



bool FadeTimer::IsDoneFadingOut()
{
	if (GetFadeOutStartTime() < 0.0f)	// Has the start time been set?
		return false;
	if (GetFadeOutEndTime() >= Clock::GetTime())	// Is the end time still to come?
		return false;
	return true;
}

