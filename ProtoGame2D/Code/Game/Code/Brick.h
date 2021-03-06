#pragma once

#include "Entity.h"

class AABB2;

class Brick : public Entity
{
public:
	AABB2 m_CollisionBox;

	explicit Brick(const Vec2& position);
	~Brick();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;
};

