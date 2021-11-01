#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

inline float toRadians(float degrees)
{
	float temp = (float)M_PI / 180.0f;
	return degrees * temp;
}