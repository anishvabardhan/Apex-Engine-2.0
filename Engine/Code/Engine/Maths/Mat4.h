#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Maths_Func.h"

struct Mat4
{
	union
	{
		float elements[4 * 4];
		Vec4 columns[4];
	};

	Mat4();

	static Mat4 identity();
	static Mat4 inverse(const Mat4& matrix);

	Mat4& Multiply(const Mat4& other);

	Mat4& operator*(const Mat4& other);
	Mat4& operator*=(const Mat4& other);
	bool operator==(const Mat4& other);
	bool operator!=(const Mat4& other);

	static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static Mat4 perspective(float fov, float aspectRatio, float near, float far);

	static Mat4 translation(const Vec3& translation);
	static Mat4 rotation(float angle, const Vec3& axis);
	static Mat4 scale(const Vec3& scale);
};