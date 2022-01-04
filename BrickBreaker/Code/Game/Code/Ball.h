#pragma once

#include "Entity.h"

class Ball : public Entity
{
public:
	Vec2 m_Accelaration;
	Vec2 m_Velocity;

	Ball();
	~Ball();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;

	void Translate(Vec2& translate);
};

