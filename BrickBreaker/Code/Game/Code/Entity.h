#pragma once

#include "Engine/Core/CoreIncludes.h"

class Game;

class Entity
{
public:
	Game* m_Owner = nullptr;
	Vec2 m_Position;
	Vec2 m_Dims;
    Vec4 m_Color;

	Entity(Game* owner, const Vec2& position, const Vec2& dims, const Vec4& color);
	~Entity();

	virtual void Update(float delatseconds);
	virtual void Render();
	virtual void DebugRender();
};
