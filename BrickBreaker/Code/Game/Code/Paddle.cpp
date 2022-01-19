#include "Paddle.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Engine/Core/GameCommon.h"
#include "Engine/Input/InputSystem.h"

extern InputSystem* g_InputSystem;

Paddle::Paddle()
	: m_Accelaration(0.0f), m_Velocity(Vec2(0.0f, 0.0f))
{
	Entity();
	m_Position = Vec2(462.0f, 20.0f);
	m_Dims = Vec2(200.0f, 25.0f);
	m_Color = Color::WHITE;
}

Paddle::~Paddle()
{
}

void Paddle::Update(float deltaseconds)
{
	UNUSED(deltaseconds);

	if(m_Position.m_X < 0.0f)
	{
		m_Position.m_X = 0.0f;
	}
	else if(m_Position.m_X + m_Dims.m_X > 1024.0f)
	{
		m_Position.m_X = 1024.0f - m_Dims.m_X;
	}
	else if(g_InputSystem->GetMousePosition().m_X <= 1024.0f - m_Dims.m_X / 2)
	{
		m_Position.m_X = g_InputSystem->GetMousePosition().m_X - m_Dims.m_X / 2;
	}
	else if(g_InputSystem->GetMousePosition().m_X >= m_Dims.m_X / 2)
	{
		m_Position.m_X = g_InputSystem->GetMousePosition().m_X - m_Dims.m_X / 2;
	}
}

void Paddle::Render()
{
	Renderer::GetInstance()->DrawQuad(m_Position, m_Dims, m_Color, BB_PADDLE_TEXTURE);
}