#pragma once

#include "Entity.h"
#include "GameCommon.h"

class AABB2;

class Brick : public Entity
{
public:
	bool m_IsDestroyed = false;
public:
	explicit Brick(Game* owner);
	explicit Brick(Game* owner, const Vec2& position);
	~Brick();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;
	virtual void DebugRender() override;
};