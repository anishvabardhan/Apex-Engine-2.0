#include "AABB2.h"

#include "Maths_Func.h"

AABB2::AABB2()
{
}

AABB2::AABB2(float minX, float minY, float maxX, float maxY)
{
	m_Mins = Vec2(minX, minY);
	m_Maxs = Vec2(maxX, maxY);
}

AABB2::AABB2(const Vec2& mins, const Vec2& maxs)
{
	this->m_Mins = mins;
	this->m_Maxs = maxs;
}

AABB2::AABB2(const Vec2& center, float radiusX, float radiusY)
{
	m_Maxs.m_X = center.m_X + radiusX;
	m_Maxs.m_Y = center.m_Y + radiusY;

	m_Mins.m_X = center.m_X - radiusX;
	m_Mins.m_Y = center.m_Y - radiusY;
}

AABB2::~AABB2()
{
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