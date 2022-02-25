#include "AABB2.h"

#include "MathUtils.h"
#include "Engine/Core/CoreMACROS.h"

STATIC const AABB2 AABB2::ZERO_TO_ONE = AABB2(0.0f, 0.0f, 1.0f, 1.0f);
STATIC const AABB2 AABB2::CENTER_PIVOT_UNIT_AABB = AABB2(-0.5f, -0.5f, 0.5f, 0.5f);
STATIC const AABB2 AABB2::CENTER_PIVOT_AABB = AABB2(-10.0f, -10.0f, 10.0f, 10.0f);

AABB2::AABB2(const Vec2& center, float radiusX, float radiusY)
{
	m_Maxs.m_X = center.m_X + radiusX;
	m_Maxs.m_Y = center.m_Y + radiusY;

	m_Mins.m_X = center.m_X - radiusX;
	m_Mins.m_Y = center.m_Y - radiusY;
}

AABB2::AABB2(const AABB2& aabb)
	:m_Mins(aabb.m_Mins), m_Maxs(aabb.m_Maxs)
{

}

AABB2::~AABB2()
{
}

Vec2 AABB2::GetNearestPoint(const Vec2& position)
{
	float x = Clamp(position.m_X, m_Mins.m_X, m_Maxs.m_X);
	float y = Clamp(position.m_Y, m_Mins.m_Y, m_Maxs.m_Y);

	return Vec2(x, y);
}

Vec2 AABB2::GetDimensions() const
{
	float width = m_Maxs.m_X - m_Mins.m_X;
	float height = m_Maxs.m_Y - m_Mins.m_Y;

	return Vec2(width, height);
}

Vec2 AABB2::GetCenter() const
{
	float x = (m_Mins.m_X + m_Maxs.m_X) * 0.5f;
	float y = (m_Mins.m_Y + m_Maxs.m_Y) * 0.5f;

	return Vec2(x, y);
}

AABB2 AABB2::operator+(const Vec2& translation)
{
	AABB2 temp;

	temp.m_Mins = m_Mins + translation;
	temp.m_Maxs = m_Maxs + translation;

	return temp;
}

AABB2 AABB2::operator-(const Vec2& translation)
{
	AABB2 temp;

	temp.m_Mins = m_Mins - translation;
	temp.m_Maxs = m_Maxs - translation;
	
	return temp;
}