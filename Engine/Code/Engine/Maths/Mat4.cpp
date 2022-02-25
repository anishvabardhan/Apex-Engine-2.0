#include "Mat4.h"



Mat4 Mat4::Inverse(const Mat4& matrix)
{
	Mat4 result;
	double det;
	double inv[4 * 4];
	double m[4 * 4];
	unsigned int index;

	for (index = 0; index < 16; index++)
	{
		m[index] = (double)matrix.elements[index];
	}

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
	det = 1.0 / det;

	for (index = 0; index < 16; index++) {
		result.elements[index] = (float)(inv[index] * det);
	}

	return result;
}

Mat4& Mat4::Multiply(const Mat4& other)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; e++)
			{
				sum += elements[x + e * 4] * other.elements[e + y * 4];
			}
			elements[x + y * 4] = sum;
		}
	}

	return *this;
}

Mat4& Mat4::operator*(const Mat4& other)
{
	return Multiply(other);
}

Mat4& Mat4::operator*=(const Mat4& other)
{
	return Multiply(other);
}

bool Mat4::operator==(const Mat4& other)
{
	int c = 0;
	for (int i = 0; i < 4 * 4; i++)
	{
		if (elements[i] == other.elements[i])
			c = 0;
		else
			c++;
	}

	if (!c)
		return true;
	return false;
}

bool Mat4::operator!=(const Mat4& other)
{
	int c = 0;
	for (int i = 0; i < 4 * 4; i++)
	{
		if (elements[i] != other.elements[i])
			c = 0;
		else
			c++;
	}

	if (!c)
		return true;
	return false;
}

Mat4 Mat4::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
	Mat4 result;

	result.elements[0] = 2.0f / (right - left);
	result.elements[5] = 2.0f / (top - bottom);
	result.elements[10] = 2.0f / (far - near);
	result.elements[12] = (right + left) / (left - right);
	result.elements[13] = (top + bottom) / (bottom - top);
	result.elements[14] = (far + near) / (near - far);
	result.elements[15] = 1.0f;

	return result;
}

Mat4 Mat4::Perspective(float fov, float aspectRatio, float near, float far)
{
	Mat4 result;

	float q = 1.0f / tanf(toRadians(0.5f * fov));
	float a = q / aspectRatio;
	float b = (near + far) * 1.0f / (far - near);
	float c = (-2.0f * far * near) * 1.0f / (far - near);

	result.elements[0] = a;
	result.elements[5] = q;
	result.elements[10] = b;
	result.elements[11] = -1.0f;
	result.elements[14] = c;

	return result;
}

Mat4 Mat4::Translation(const Vec3& translation)
{
	Mat4 result;
	result = Identity();
	
	result.elements[12] = translation.m_X;
	result.elements[13] = translation.m_Y;
	result.elements[14] = translation.m_Z;

	return result;
}

Mat4 Mat4::Rotation2D(float angle)
{
	Mat4 result;

	result = Mat4::Identity();

	result.elements[0] =  cosf(toRadians(angle));
	result.elements[1] =  sinf(toRadians(angle));
						  
	result.elements[4] =  -sinf(toRadians(angle));
	result.elements[5] =  cosf(toRadians(angle));

	return result;
}

Mat4 Mat4::Scale(const Vec3& scale)
{
	Mat4 result;

	result.elements[0] = scale.m_X;
	result.elements[5] = scale.m_Y;
	result.elements[10] = scale.m_Z;
	result.elements[15] = 1.0f;

	return result;
}