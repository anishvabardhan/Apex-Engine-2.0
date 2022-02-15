#pragma once

#include <iostream>

class Vec4
{
public:
	float m_X;
	float m_Y;
	float m_Z;
	float m_W;

	static const Vec4 ZERO;
	static const Vec4 ONE;
	static const Vec4 UNIT_X;
	static const Vec4 UNIT_Y;
	static const Vec4 UNIT_Z;
	static const Vec4 UNIT_W;
public:
	Vec4() = default;
	explicit Vec4(float x, float y, float z, float w);

	Vec4 operator+(const Vec4& other);
	Vec4 operator-(const Vec4& other);
	Vec4 operator*(const Vec4& other);
	Vec4 operator/(const Vec4& other);

	Vec4& operator+=(const Vec4& other);
	Vec4& operator-=(const Vec4& other);
	Vec4& operator*=(const Vec4& other);
	Vec4& operator/=(const Vec4& other);

	bool operator==(const Vec4& other);
	bool operator!=(const Vec4& other);

	friend std::ostream& operator<<(std::ostream& stream, const Vec4& vector);
};