#pragma once

#include "Vec2.h"

class AABB2
{
public:
	Vec2 m_Mins;
	Vec2 m_Maxs;
public:
	AABB2();
	explicit AABB2(float minX, float minY, float maxX, float maxY);
	explicit AABB2(const Vec2& mins, const Vec2& maxs);
	explicit AABB2(const Vec2& center, float radiusX, float radiusY);
	~AABB2();

	Vec2 GetDimensions() const;
	Vec2 GetCenter() const;

	AABB2 operator +(const Vec2& translation);
	AABB2 operator -(const Vec2& translation);
};