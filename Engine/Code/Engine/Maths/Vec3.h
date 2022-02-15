#pragma once

#include <iostream>

class Vec3
{
public:
	float m_X;
	float m_Y;
	float m_Z;

	static const Vec3 ZERO;
	static const Vec3 ONE;
	static const Vec3 UNIT_X;
	static const Vec3 UNIT_Y;
	static const Vec3 UNIT_Z;
public:
	Vec3();
	explicit Vec3(float x, float y, float z);

	Vec3 operator+(const Vec3& other);
	Vec3 operator-(const Vec3& other);
	Vec3 operator*(const Vec3& other);
	Vec3 operator/(const Vec3& other);

	Vec3& operator+=(const Vec3& other);
	Vec3& operator-=(const Vec3& other);
	Vec3& operator*=(const Vec3& other);
	Vec3& operator/=(const Vec3& other);

	bool operator==(const Vec3& other);
	bool operator!=(const Vec3& other);

	friend std::ostream& operator<<(std::ostream& stream, const Vec3& vector);
};