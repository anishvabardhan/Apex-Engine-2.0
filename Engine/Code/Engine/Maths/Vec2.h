#pragma once

#include <iostream>

class Vec2
{
public:
	float m_X;
	float m_Y;
public:
	Vec2();
	explicit Vec2(float x, float y);

	Vec2& Add(const Vec2& other);
	Vec2& Subtract( const Vec2& other);
	Vec2& Multiply(const Vec2& other);
	Vec2& Divide(const Vec2& other);

	Vec2& operator+(const Vec2& other);
	Vec2& operator-(const Vec2& other);
	Vec2& operator*(const Vec2& other);
	Vec2& operator/(const Vec2& other);

	Vec2 operator+=(const Vec2& other);
	Vec2 operator-=(const Vec2& other);
	Vec2 operator*=(const Vec2& other);
	Vec2 operator/=(const Vec2& other);

	bool operator==(const Vec2& other);
	bool operator!=(const Vec2& other);

	const Vec2 operator*(float Scale) const;
	const Vec2 operator/(float inverseScale) const;

	inline float GetLength() const { return sqrtf((m_X * m_X) + (m_Y * m_Y)); }
	inline Vec2 GetNormalised() const { Vec2 temp = Vec2(m_X, m_Y) / GetLength(); return temp; }

	friend std::ostream& operator<<(std::ostream& stream, const Vec2& vector);
};