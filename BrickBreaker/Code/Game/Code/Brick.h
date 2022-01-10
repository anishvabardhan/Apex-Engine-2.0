#pragma once

#include "Engine/Core/GameCommon.h"
#include "Entity.h"

class AABB2;

class Brick : public Entity
{
public:
	AABB2 m_CollisionBox;
	bool m_IsDestroyed[NUM_OF_BRICKS / 8][NUM_OF_BRICKS / 4];

	Brick();
	explicit Brick(const Vec2& position);
	~Brick();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;
};

