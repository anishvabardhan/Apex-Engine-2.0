#include "Brick.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Engine/Core/GameCommon.h"

Brick::Brick(const Vec2& position)
{
	Entity();
	m_Position = position;
	m_Dims = Vec2(124.0f, 48.0f);
	m_Color = Color::YELLOW;
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
	Renderer::GetInstance()->DrawQuad(m_Position, m_Dims, m_Color, APEX_DEFAULT_TEXTURE);
}
