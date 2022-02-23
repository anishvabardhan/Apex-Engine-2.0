#pragma once

#include "Entity.h"

class Paddle : public Entity
{
public:
    float m_Accelaration;
	Vec2 m_Velocity;

	explicit Paddle(Game* owner);
	~Paddle();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;
	virtual void DebugRender() override;
};