#include "Brick.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"

extern Renderer* g_Renderer; 

Brick::Brick(Game* owner)
	:Entity(owner, Vec2(0.0f, 0.0f), BB_BRICK_DIMS, Color::WHITE)
{
}

Brick::Brick(Game* owner, const Vec2& position)
	:	Entity(owner, position, BB_BRICK_DIMS, Color::WHITE)
{
}

Brick::~Brick()
{
}

void Brick::Update(float deltaseconds)
{
	UNUSED(deltaseconds)
}

void Brick::Render()
{
    if(!m_IsDestroyed)
    {
    	AABB2 aabb2(m_Position, m_Position + m_Dims);
    	g_Renderer->SetModelTranslation();
    	g_Renderer->DrawAABB2(aabb2, m_Color);
    }
}

void Brick::DebugRender()
{
    if(!m_IsDestroyed)
    {
    	AABB2 aabb2(m_Position, m_Position + m_Dims);
    	g_Renderer->SetModelTranslation();
    	g_Renderer->DrawHollowAABB2(aabb2, 5.0f, Color::MAGENTA);
    }
}
