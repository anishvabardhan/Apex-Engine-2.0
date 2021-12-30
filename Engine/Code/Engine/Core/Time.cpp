#include "Time.h"

#include <ctime>
#include "Engine/Platform/WindowsH.h"
#include <cstdlib>

Time::Time(float fps)
	:m_FPS(fps)
{
	LARGE_INTEGER t;
	QueryPerformanceFrequency(&t);
	m_Frequency = t.QuadPart;

	Reset();
}

Time::~Time()
{
}

void Time::Reset()
{
	// Set the Current Time
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	m_StartTime = t.QuadPart;
	m_CurrentCallToUpdate = t.QuadPart;
	m_LastCallToUpdate = t.QuadPart;
}

void Time::Update()
{
	m_LastCallToUpdate = m_CurrentCallToUpdate;
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	m_CurrentCallToUpdate = t.QuadPart;
}

float Time::GetTimeDelta()
{
	float d = (float)(m_CurrentCallToUpdate - m_LastCallToUpdate);

	if (d > m_FPS)
		d = m_FPS;

	return 1.0f / d;
}