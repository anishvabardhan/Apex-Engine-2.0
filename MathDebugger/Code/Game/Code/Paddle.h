#pragma once

#include "Entity.h"

class Paddle : public Entity
{
public:
	Vec2 m_Velocity;
    float m_Accelaration;

	Paddle();
	~Paddle();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;
};

