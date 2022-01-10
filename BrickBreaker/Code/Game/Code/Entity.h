#pragma once

#include "Engine/Core/CoreIncludes.h"

class Entity
{
public:
	Vec2 m_Position;
	Vec2 m_Dims;
    Vec4 m_Color;

	Entity();
	~Entity();

	virtual void Update(float delatseconds);
	virtual void Render();
};