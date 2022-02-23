#include "MathUtils.h"

#include "AABB2.h"
#include "Maths_Func.h"
#include"Vec2.h"

float Clamp(float value, float min, float max)
{
	if(value > max)
	{
		return max;
	}

	if(value < min)
	{
		return min;
	}
	
	return value;
}

float CosDegrees(float degrees)
{
	return cos(toRadians(degrees));
}

float SinDegrees(float degrees)
{
	return sin(toRadians(degrees));
}

float Atan2Degrees(float y, float x)
{
	return toDegrees(atan2f(y, x));
}

float RangeMap(float inputValue, float inputBegin, float inputEnd, float outputBegin, float outputEnd)
{
	float inputRange = inputEnd - inputBegin;
	float outputRange = outputEnd - outputBegin;

	float inputRelative = inputValue - inputBegin;

	float inputRelativeFraction = inputRelative / inputRange;

	float outValue = (inputRelativeFraction * outputRange) + outputBegin;

	return outValue;
}

bool Disc_AABB2Collision(const Vec2& center, const float& radius, AABB2& box)
{
	Vec2 nearestPoint = box.GetNearestPoint(center);

	float distSquared = ((nearestPoint.m_X - center.m_X) * (nearestPoint.m_X - center.m_X)) + ((nearestPoint.m_Y - center.m_Y) * (nearestPoint.m_Y - center.m_Y));
	float radSquared = radius * radius;

	return (distSquared <= radSquared);
}