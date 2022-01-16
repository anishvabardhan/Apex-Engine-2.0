#pragma once

#include "Engine/Core/GameCommon.h"
#include "Entity.h"

class AABB2;

class Brick : public Entity
{
public:
	AABB2 m_CollisionBox;
	bool m_IsDestroyed[NUM_OF_ROWS][NUM_OF_COLS];

	Brick();
	explicit Brick(const Vec2& position);
	~Brick();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;
};

