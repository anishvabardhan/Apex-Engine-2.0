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

	::ScreenToClient((HWND) Window::GetInstance()->GetHandle(), &screenPos);
	POINT clientPos = screenPos; 

	RECT rectTemp;
	GetWindowRect((HWND)Window::GetInstance()->GetHandle(), &rectTemp);

	return Vec2( (float) clientPos.x, rectTemp.bottom - rectTemp.top - (float)clientPos.y);
}

void Mouse::SetMouseScreenPosition(const Vec2& desktopPos)
{
	POINT clientPos;
	clientPos.x = (int) desktopPos.m_X;
	clientPos.y = (int) desktopPos.m_Y;
	::ClientToScreen((HWND) Window::GetInstance()->GetHandle(), &clientPos);

	::SetCursorPos( (int) clientPos.x, (int) clientPos.y );
}
