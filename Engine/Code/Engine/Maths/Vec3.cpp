#include "Vec3.h"

	Vec3::Vec3()
		: m_X(0), m_Y(0), m_Z(0)
	{
	}

	Vec3::Vec3(float x, float y, float z)
		: m_X(x), m_Y(y), m_Z(z)
	{
	}

	Vec3& Vec3::Add(const Vec3& other)
	{
		m_X += other.m_X;
		m_Y += other.m_Y;
		m_Z += other.m_Z;
		return *this;
	}

	Vec3& Vec3::Subtract(const Vec3& other)
	{
		m_X -= other.m_X;
		m_Y -= other.m_Y;
		m_Z -= other.m_Z;
		return *this;
	}

	Vec3& Vec3::Multiply(const Vec3& other)
	{
		m_X *= other.m_X;
		m_Y *= other.m_Y;
		m_Z *= other.m_Z;
		return *this;
	}

	Vec3& Vec3::Divide(const Vec3& other)
	{
		m_X /= other.m_X;
		m_Y /= other.m_Y;
		m_Z /= other.m_Z;
		return *this;
	}

	Vec3& Vec3::operator+(const Vec3& other)
	{
		return Add(other);
	}

	Vec3& Vec3::operator-(const Vec3& other)
	{
		return Subtract(other);
	}

	Vec3& Vec3::operator*(const Vec3& other)
	{
		return Multiply(other);
	}

	Vec3& Vec3::operator/(const Vec3& other)
	{
		return Divide(other);
	}

	Vec3 Vec3::operator+=(const Vec3& other)
	{
		return Add(other);
	}

	Vec3 Vec3::operator-=(const Vec3& other)
	{
		return Subtract(other);
	}

	Vec3 Vec3::operator*=(const Vec3& other)
	{
		return Multiply(other);
	}

	Vec3 Vec3::operator/=(const Vec3& other)
	{
		return Divide(other);
	}

	bool Vec3::operator==(const Vec3& other)
	{
		return this->m_X == other.m_X && this->m_Y == other.m_Y && this->m_Z == other.m_Z;
	}

	bool Vec3::operator!=(const Vec3& other)
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec3& vector)
	{
		stream << "(" << vector.m_X << ", " << vector.m_Y << ", " << vector.m_Z << ")";
		return stream;
	}