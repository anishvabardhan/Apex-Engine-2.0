#include "Random.h"

#include <stdlib.h>

Random::Random(float minInclusive, float maxInclusive)
	:min(minInclusive), max(maxInclusive)
{
}

Random::Random(float rangeMinMax)
	:min(rangeMinMax), max(rangeMinMax)
{
}

float Random::GetRandomInRange()
{
	return GetRandomFloatInRange(min, max);
}

int Random::GetRandomIntLessThan(int maxNotInclusive)
{
	return rand() % maxNotInclusive;
}

float Random::GetRandomFloatInRange(float minInclusive, float maxInclusive)
{
	float range = (maxInclusive - minInclusive) + 1;
	return (float)minInclusive + (float)GetRandomIntLessThan((int)range);
}

int Random::GetRandomIntInRange(int minInclusive, int maxInclusive)
{
	int range = (maxInclusive - minInclusive) + 1;
	return minInclusive + GetRandomIntLessThan(range);
}

float Random::Interpolate(float start, float end, float fractionTowardEnd)
{
	float range = end - start;
	float fractionValue = fractionTowardEnd * range;

	return fractionValue + start;
}

const Random Random::Interpolate(const Random& start, const Random& end, float fractionTowardEnd)
{
	Random temp;
	temp.min = Interpolate(start.min, end.min, fractionTowardEnd);
	temp.max = Interpolate(start.max, end.max, fractionTowardEnd);
	return temp;
}