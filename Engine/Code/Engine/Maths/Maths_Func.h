#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

inline float toRadians(float degrees)
{
	float temp = (float)M_PI / 180.0f;
	return degrees * temp;
}

inline float toDegrees(float radians)
{
	float temp = radians * 180.0f * 0.3183098f;
	return temp;
}