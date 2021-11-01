#pragma once

#include "Engine/Core/CoreIncludes.h"

class Bullet
{
public:
	Vec2 m_Position;
	Vec2 m_Velocity;

	Vec3 m_BodyVertices[10];

	int m_NumOfVertices;

	float m_Age;
	float m_Radius;
public:
	explicit Bullet(const Vec2& position);
	~Bullet();

	void OnUpdate(Vec2 update, float dt);
	void Render();

	inline float GetAge() { return m_Age; }
	inline Vec2 GetPosition() { return m_Position; }
};