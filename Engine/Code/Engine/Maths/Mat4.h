#pragma once
#pragma warning( disable : 4201)

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Maths_Func.h"

struct Mat4
{
	union
	{
		float elements[16];
		Vec4 columns[4];
		struct
		{
			float Ix;
		    float Iy;
		    float Iz;	
		    float Iw;
		    float Jx;	
		    float Jy;	
		    float Jz;
		    float Jw;
		    float Kx;
		    float Ky;
		    float Kz;
		    float Kw;
		    float Tx;
		    float Ty;
		    float Tz;
		    float Tw;
		};
	};

	constexpr Mat4();

	static constexpr Mat4 Identity() { return Mat4();}
	static Mat4 Inverse(const Mat4& matrix);

	Mat4& Multiply(const Mat4& other);

	Mat4& operator*(const Mat4& other);
	Mat4& operator*=(const Mat4& other);
	bool operator==(const Mat4& other);
	bool operator!=(const Mat4& other);

	static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
	static Mat4 Perspective(float fov, float aspectRatio, float near, float far);

	static Mat4 Translation(const Vec3& translation);
	static Mat4 Rotation2D(float angle);
	static Mat4 Scale(const Vec3& scale);
};

constexpr Mat4::Mat4()
	: Ix(1.0f),
      Iy(0.0f),
      Iz(0.0f),	
      Iw(0.0f),
      Jx(0.0f),	
      Jy(1.0f),	
      Jz(0.0f),
      Jw(0.0f),
      Kx(0.0f),
      Ky(0.0f),
      Kz(1.0f),
      Kw(0.0f),
      Tx(0.0f),
      Ty(0.0f),
      Tz(0.0f),
      Tw(1.0f)
{
}