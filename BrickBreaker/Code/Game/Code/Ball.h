#pragma once

#include "Entity.h"

class Ball : public Entity
{
public:
	Vec2 m_Translate;
	Vec2 m_Velocity;
	Vec2 m_Center;
	float m_Radius;

	Ball();
	~Ball();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;

	void Translate(const Vec2& translate);

	static void CreateInstance();
	static Ball* GetInstance();
	static void DestroyInstance();
};

