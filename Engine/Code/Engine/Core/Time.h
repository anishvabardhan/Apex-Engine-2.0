#pragma once

class Time
{
	float m_FPS;
	long long m_StartTime, m_LastCallToUpdate, m_CurrentCallToUpdate, m_Frequency;
public:
	Time(float fps);
	~Time();

	void Reset();
	void Update();
	float GetTimeDelta();
};