#include "Mouse.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Engine/Window/Window.h"

void Mouse::UpdateMouse()
{
	if(Window::GetInstance())
	{
		m_PositionLastFrame = m_PositionThisFrame;
		m_PositionThisFrame = GetMouseClientPosition();
	}
}

Vec2 Mouse::GetMouseDelta()
{
	return m_PositionThisFrame - m_PositionLastFrame;
}

Vec2 Mouse::GetMouseScreenPosition() const
{
	POINT screenPos;
	::GetCursorPos( &screenPos );

	return Vec2((float) screenPos.x, (float) screenPos.y);
}

Vec2 Mouse::GetMouseClientPosition() const
{
	POINT screenPos;
	::GetCursorPos( &screenPos );

	::ScreenToClient((HWND) Window::GetInstance()->GetHandle(), &screenPos);
	POINT clientPos = screenPos; 

	return Vec2( (float) clientPos.x, (float) clientPos.y);
}

void Mouse::SetMouseScreenPosition(const Vec2& desktopPos)
{
	::SetCursorPos( (int) desktopPos.m_X, (int) desktopPos.m_Y );
}

void Mouse::SetMouseClientPosition(const Vec2& clientPos)
{
	POINT desktopPos;
	desktopPos.x = (int) clientPos.m_X;
	desktopPos.y = (int) clientPos.m_Y;
	::ClientToScreen((HWND) Window::GetInstance()->GetHandle(), &desktopPos);

	SetMouseScreenPosition(Vec2((float) desktopPos.x, (float) desktopPos.y));
}
