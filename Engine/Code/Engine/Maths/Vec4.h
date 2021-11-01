#pragma once

#include <iostream>

class Vec4
{
public:
	float m_X;
	float m_Y;
	float m_Z;
	float m_W;
public:
	Vec4() = default;
	explicit Vec4(float x, float y, float z, float w);

	Vec4& Add(const Vec4& other);
	Vec4& Subtract( const Vec4& other);
	Vec4& Multiply(const Vec4& other);
	Vec4& Divide(const Vec4& other);

	Vec4& operator+(const Vec4& other);
	Vec4& operator-(const Vec4& other);
	Vec4& operator*(const Vec4& other);
	Vec4& operator/(const Vec4& other);

	Vec4 operator+=(const Vec4& other);
	Vec4 operator-=(const Vec4& other);
	Vec4 operator*=(const Vec4& other);
	Vec4 operator/=(const Vec4& other);

	bool operator==(const Vec4& other);
	bool operator!=(const Vec4& other);

	friend std::ostream& operator<<(std::ostream& stream, const Vec4& vector);
};