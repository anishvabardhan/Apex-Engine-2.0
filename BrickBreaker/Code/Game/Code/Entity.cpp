#include "Entity.h"

Entity::Entity(Game* owner, const Vec2& position, const Vec2& dims, const Vec4& color)
	:m_Owner(owner), m_Position(position), m_Dims(dims), m_Color(color)
{
}

Entity::~Entity()
{
	m_Owner = nullptr;
}

void Entity::Update(float delatseconds)
{
	UNUSED(delatseconds);
}

void Entity::Render()
{
}

void Entity::DebugRender()
{
}
