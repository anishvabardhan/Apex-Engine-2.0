#pragma once

#include "CoreIncludes.h"

class Time
{
	float m_FPS;
	uint64_t m_StartTime;
	uint64_t m_LastCallToUpdate;
	uint64_t m_CurrentCallToUpdate;
	uint64_t m_Frequency;
public:
	Time(float fps);
	~Time();

	void Reset();
	void Update();
	float GetTimeDelta();
};
