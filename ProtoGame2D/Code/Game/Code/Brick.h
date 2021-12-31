#pragma once

#include "Entity.h"

class Brick : public Entity
{
public:
	Brick();
	~Brick();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;
};

