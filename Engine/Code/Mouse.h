#pragma once

#include "Engine/Maths/Vec2.h"

class Mouse
{
	Vec2 m_PositionLastFrame;
	Vec2 m_PositionThisFrame;
public:
	Mouse();
	~Mouse();

	void UpdateMouse();

	Vec2 GetMouseDelta();
	Vec2 GetMouseScreenPosition();
		 
	void SetMouseScreenPosition( const Vec2& desktopPos );
};