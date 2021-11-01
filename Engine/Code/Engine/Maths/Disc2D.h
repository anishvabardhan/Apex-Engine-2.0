#pragma once

#include "Vec2.h"

class Disc2D
{
	Vec2 m_Center;
	float m_Radius;
public:
	explicit Disc2D(Vec2 position, float radius);
	~Disc2D();

	static bool CheckCollision(Disc2D* obj1, Disc2D* obj2);

	inline float GetRadius() const { return m_Radius; }
	inline Vec2 GetCenter() const { return m_Center; }
};