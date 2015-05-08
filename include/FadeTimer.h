#pragma once


class FadeTimer {
public:
	FadeTimer();
	~FadeTimer();
	
	void SetFadeIn(float waitFor, float fadeFor);
	void SetFadeOut(float waitFor, float fadeFor);
	float GetFadeInStartTime();
	float GetFadeInEndTime();
	float GetFadeOutStartTime();
	float GetFadeOutEndTime();
	
	void StartFadeIn(bool fadeOutAfter);
	void StartFadeOut();
	
	void SetAlphaMin(float min);
	void SetAlphaMax(float max);
	float GetAlpha();
	
	bool IsFadingIn();
	bool IsFadingOut();
	bool IsDoneFadingIn();
	bool IsDoneFadingOut();

private:
	float m_inStartTime;
	float m_inWaitFor;
	float m_inFadeFor;
	float m_outStartTime;
	float m_outWaitFor;
	float m_outFadeFor;
	float m_alphaMin;
	float m_alphaMax;
};
