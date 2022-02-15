#pragma once

#include "Vec2.h"

class AABB2
{
public:
	Vec2 m_Mins;
	Vec2 m_Maxs;

	static const AABB2 ZERO_TO_ONE;
	static const AABB2 CENTER_PIVOT_UNIT_AABB;
	static const AABB2 CENTER_PIVOT_AABB;
public:
	constexpr AABB2() = default;
	constexpr explicit AABB2(float minX, float minY, float maxX, float maxY): m_Mins(Vec2(minX, minY)), m_Maxs(Vec2(maxX, maxY)) {}
	explicit AABB2(const Vec2& mins, const Vec2& maxs): m_Mins(mins), m_Maxs(maxs) {}
	explicit AABB2(const Vec2& center, float radiusX, float radiusY);
	AABB2(const AABB2& aabb);
	~AABB2();

	Vec2 GetNearestPoint(const Vec2& position);
	Vec2 GetDimensions() const;
	Vec2 GetCenter() const;

	AABB2 operator +(const Vec2& translation);
	AABB2 operator -(const Vec2& translation);
};