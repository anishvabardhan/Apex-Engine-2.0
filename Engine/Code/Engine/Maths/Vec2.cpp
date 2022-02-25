#include "Vec2.h"

#include "Maths.h"
#include "MathUtils.h"
#include "Engine/Core/CoreMACROS.h"

STATIC const Vec2 Vec2::ZERO_ZERO;
STATIC const Vec2 Vec2::ZERO_ONE = Vec2(0.0f, 1.0f);
STATIC const Vec2 Vec2::HALF_ONE = Vec2(0.5f, 1.0f);
STATIC const Vec2 Vec2::ONE_ZERO = Vec2(1.0f, 0.0f);
STATIC const Vec2 Vec2::ONE_ONE = Vec2(1.0f, 1.0f);

Vec2::Vec2(const Vec2& other)
	:m_X(other.m_X), m_Y(other.m_Y)
{
}

Vec2 Vec2::operator+(const Vec2& other)
{
	return Vec2(m_X + other.m_X, m_Y + other.m_Y);
}

Vec2 Vec2::operator-(const Vec2& other)
{
	return Vec2(m_X - other.m_X, m_Y - other.m_Y);
}

Vec2 Vec2::operator*(const Vec2& other)
{
	return Vec2(m_X * other.m_X, m_Y * other.m_Y);
}

Vec2 Vec2::operator/(const Vec2& other)
{
	return Vec2(m_X / other.m_X, m_Y / other.m_Y);
}

Vec2& Vec2::operator+=(const Vec2& other)
{
	m_X += other.m_X;
	m_Y += other.m_Y;

	return *this;
}

Vec2& Vec2::operator-=(const Vec2& other)
{
	m_X -= other.m_X;
	m_Y -= other.m_Y;

	return *this;
}

Vec2& Vec2::operator*=(const Vec2& other)
{
	m_X *= other.m_X;
	m_Y *= other.m_Y;

	return *this;
}

Vec2& Vec2::operator/=(const Vec2& other)
{
	m_X /= other.m_X;
	m_Y /= other.m_Y;

	return *this;
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

float Vec2::GetLength() const
{
	return sqrtf((m_X * m_X) + (m_Y * m_Y));
}

void Vec2::SetLength(float length)
{
	float theta = GetAngleDegrees();

	m_X = length * CosDegrees(theta);
	m_Y = length * SinDegrees(theta);
}

float Vec2::GetAngleDegrees() const
{
	return Atan2Degrees(m_Y, m_X);
}

float Vec2::GetLengthSquared() const
{
	return (m_X * m_X) + (m_Y * m_Y);
}

Vec2 Vec2::GetNormalised() const
{
	Vec2 temp = Vec2(m_X, m_Y) / GetLength();

	return temp;
}

Vec2 Vec2::Reflected(const Vec2& normalVector)
{
	return *this - (normalVector * 2 * (DotProduct2D(*this , normalVector)));
}

Vec2 Vec2::GetRotated90Degrees() const
{
	return Vec2(-m_Y, m_X);
}

float Vec2::DotProduct2D(const Vec2& first, const Vec2& second)
{
	return (( first.m_X * second.m_X ) + ( first.m_Y * second.m_Y ));
}

Vec2 Vec2::MakeFromPolarDegrees(float directionDegrees, float length)
{
	Vec2 result;

	result.m_X = length * CosDegrees(directionDegrees);
	result.m_Y = length * SinDegrees(directionDegrees);

	return result;
}

std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
{
	stream << "(" << vector.m_X << ", " << vector.m_Y << ")";

	return stream;
}