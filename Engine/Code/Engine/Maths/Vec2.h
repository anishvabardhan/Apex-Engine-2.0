#pragma once

#include <iostream>

class Vec2
{
public:
	float m_X;
	float m_Y;

	static const Vec2 ZERO_ZERO;
	static const Vec2 ZERO_ONE;
	static const Vec2 HALF_ONE;
	static const Vec2 ONE_ZERO;
	static const Vec2 ONE_ONE;
public:
	constexpr Vec2(): m_X(0), m_Y(0) {}
	constexpr explicit Vec2(const float x, const float y): m_X(x), m_Y(y) {}
	Vec2(const Vec2& other);

	Vec2 operator+(const Vec2& other);
	Vec2 operator-(const Vec2& other);
	Vec2 operator*(const Vec2& other);
	Vec2 operator/(const Vec2& other);

	Vec2& operator+=(const Vec2& other);
	Vec2& operator-=(const Vec2& other);
	Vec2& operator*=(const Vec2& other);
	Vec2& operator/=(const Vec2& other);

	bool operator==(const Vec2& other);
	bool operator!=(const Vec2& other);

	const Vec2 operator*(float Scale) const;
	const Vec2 operator/(float inverseScale) const;

	void SetLength(float length);

	float GetAngleDegrees() const;
	Vec2 GetRotated90Degrees() const;
	float GetLength() const;
	float GetLengthSquared() const;
	Vec2 GetNormalised() const;

	Vec2 Vec2::Reflected( const Vec2& normalVector );
	float DotProduct2D( const Vec2& first , const Vec2& second );

	static Vec2 MakeFromPolarDegrees(float directionDegrees, float length);

	friend std::ostream& operator<<(std::ostream& stream, const Vec2& vector);
};