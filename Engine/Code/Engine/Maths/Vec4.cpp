#include "Vec4.h"

#include "Engine/Core/CoreMACROS.h"

STATIC const Vec4 Vec4::ZERO = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
STATIC const Vec4 Vec4::ONE = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
STATIC const Vec4 Vec4::UNIT_X = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
STATIC const Vec4 Vec4::UNIT_Y = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
STATIC const Vec4 Vec4::UNIT_Z = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
STATIC const Vec4 Vec4::UNIT_W = Vec4(0.0f, 0.0f, 0.0f, 1.0f);

Vec4 Vec4::operator+(const Vec4& other)
{
	return Vec4(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z, m_W + other.m_W);
}

Vec4 Vec4::operator-(const Vec4& other)
{
	return Vec4(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z, m_W - other.m_W);
}

Vec4 Vec4::operator*(const Vec4& other)
{
	return Vec4(m_X * other.m_X, m_Y * other.m_Y, m_Z * other.m_Z, m_W * other.m_W);
}

Vec4 Vec4::operator/(const Vec4& other)
{
	return Vec4(m_X / other.m_X, m_Y / other.m_Y, m_Z / other.m_Z, m_W / other.m_W);
}

Vec4& Vec4::operator+=(const Vec4& other)
{
    m_X += other.m_X;
	m_Y += other.m_Y;
	m_Z += other.m_Z;
	m_W += other.m_W;
	return *this;
}

Vec4& Vec4::operator-=(const Vec4& other)
{
    m_X -= other.m_X;
	m_Y -= other.m_Y;
	m_Z -= other.m_Z;
	m_W -= other.m_W;
	return *this;
}

Vec4& Vec4::operator*=(const Vec4& other)
{
    m_X *= other.m_X;
	m_Y *= other.m_Y;
	m_Z *= other.m_Z;
	m_W *= other.m_W;
	return *this;
}

Vec4& Vec4::operator/=(const Vec4& other)
{
    m_X /= other.m_X;
	m_Y /= other.m_Y;
	m_Z /= other.m_Z;
	m_W /= other.m_W;
	return *this;
}

bool Vec4::operator==(const Vec4& other)
{
	return this->m_X == other.m_X && this->m_Y == other.m_Y && this->m_Z == other.m_Z && this->m_W == other.m_W;
}

bool Vec4::operator!=(const Vec4& other)
{
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& stream, const Vec4& vector)
{
	stream << "(" << vector.m_X << ", " << vector.m_Y << ", " << vector.m_Z << ", " << vector.m_W << ")";
	return stream;
}