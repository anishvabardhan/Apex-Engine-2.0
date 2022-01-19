#include "Mouse.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Engine/Window/Window.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::UpdateMouse()
{
	if(Window::GetInstance())
	{
		m_PositionLastFrame = m_PositionThisFrame;
		m_PositionThisFrame = GetMouseScreenPosition();
	}
}

Vec2 Mouse::GetMouseDelta()
{
	return m_PositionThisFrame - m_PositionLastFrame;
}

Vec2 Mouse::GetMouseScreenPosition()
{
	POINT screenPos;
	::GetCursorPos( &screenPos );

	return Vec2((float) screenPos.x, (float) screenPos.y);
}

void Mouse::SetMouseScreenPosition(const Vec2& desktopPos)
{
	::SetCursorPos( (int) desktopPos.m_X, (int) desktopPos.m_Y );
}
