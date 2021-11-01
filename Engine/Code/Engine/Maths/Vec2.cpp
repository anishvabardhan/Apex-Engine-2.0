#include "Vec2.h"

Vec2::Vec2()
	: m_X(0), m_Y(0)
{
}

Vec2::Vec2(float x, float y)
	: m_X(x), m_Y(y)
{
}

Vec2& Vec2::Add(const Vec2& other)
{
	m_X += other.m_X;
	m_Y += other.m_Y;

	return *this;
}

Vec2& Vec2::Subtract(const Vec2& other)
{
	m_X -= other.m_X;
	m_Y -= other.m_Y;

	return *this;
}

Vec2& Vec2::Multiply(const Vec2& other)
{
	m_X *= other.m_X;
	m_Y *= other.m_Y;

	return *this;
}

Vec2& Vec2::Divide(const Vec2& other)
{
	m_X /= other.m_X;
	m_Y /= other.m_Y;

	return *this;
}

Vec2& Vec2::operator+(const Vec2& other)
{
	return Add(other);
}

Vec2& Vec2::operator-(const Vec2& other)
{
	return Subtract(other);
}

Vec2& Vec2::operator*(const Vec2& other)
{
	return Multiply(other);
}

Vec2& Vec2::operator/(const Vec2& other)
{
	return Divide(other);
}

Vec2 Vec2::operator+=(const Vec2& other)
{
	return Add(other);
}

Vec2 Vec2::operator-=(const Vec2& other)
{
	return Subtract(other);
}

Vec2 Vec2::operator*=(const Vec2& other)
{
	return Multiply(other);
}

Vec2 Vec2::operator/=(const Vec2& other)
{
	return Divide(other);
}

bool Vec2::operator==(const Vec2& other)
{
	return this->m_X == other.m_X && this->m_Y == other.m_Y;
}

bool Vec2::operator!=(const Vec2& other)
{
	return !(*this == other);
}

const Vec2 Vec2::operator*(float Scale) const
{
	return Vec2(m_X * Scale, m_Y * Scale);
}

const Vec2 Vec2::operator/(float inverseScale) const
{
	return Vec2(m_X / inverseScale, m_Y / inverseScale);
}

std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
{
	stream << "(" << vector.m_X << ", " << vector.m_Y << ")";

	return stream;
}