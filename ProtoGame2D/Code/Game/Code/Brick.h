#pragma once

#include "Entity.h"

class Brick : public Entity
{
public:
	explicit Brick(const Vec2& position);
	~Brick();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;
};

