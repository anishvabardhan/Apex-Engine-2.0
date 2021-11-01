#include "Vec4.h"

Vec4::Vec4(float x, float y, float z, float w)
	: m_X(x), m_Y(y), m_Z(z), m_W(w)
{
}

Vec4& Vec4::Add(const Vec4& other)
{
	m_X += other.m_X;
	m_Y += other.m_Y;
	m_Z += other.m_Z;
	m_W += other.m_W;
	return *this;
}

Vec4& Vec4::Subtract(const Vec4& other)
{
	m_X -= other.m_X;
	m_Y -= other.m_Y;
	m_Z -= other.m_Z;
	m_W -= other.m_W;
	return *this;
}

Vec4& Vec4::Multiply(const Vec4& other)
{
	m_X *= other.m_X;
	m_Y *= other.m_Y;
	m_Z *= other.m_Z;
	m_W *= other.m_W;
	return *this;
}

Vec4& Vec4::Divide(const Vec4& other)
{
	m_X /= other.m_X;
	m_Y /= other.m_Y;
	m_Z /= other.m_Z;
	m_W /= other.m_W;
	return *this;
}

Vec4& Vec4::operator+(const Vec4& other)
{
	return Add(other);
}

Vec4& Vec4::operator-(const Vec4& other)
{
	return Subtract(other);
}

Vec4& Vec4::operator*(const Vec4& other)
{
	return Multiply(other);
}

Vec4& Vec4::operator/(const Vec4& other)
{
	return Divide(other);
}

Vec4 Vec4::operator+=(const Vec4& other)
{
	return Add(other);
}

Vec4 Vec4::operator-=(const Vec4& other)
{
	return Subtract(other);
}

Vec4 Vec4::operator*=(const Vec4& other)
{
	return Multiply(other);
}

Vec4 Vec4::operator/=(const Vec4& other)
{
	return Divide(other);
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