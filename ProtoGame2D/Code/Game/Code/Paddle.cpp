#include "Paddle.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Engine/Core/GameCommon.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Input/WinKeys.h"

extern InputSystem* g_InputSystem;

Paddle::Paddle()
	: m_Accelaration(0.0f), m_Velocity(Vec2(0.0f, 0.0f))
{
	Entity();
	m_Position = Vec2(512.0f, 200.0f);
	m_Dims = Vec2(100.0f, 25.0f);
	m_Color = Color::CYAN;
}

Paddle::~Paddle()
{
}

void Paddle::Update(float deltaseconds)
{
	if(g_InputSystem->IsHeldDown(D))
	{
		m_Accelaration = 500.0f;
	}
	else if(g_InputSystem->IsHeldDown(A))
	{
		m_Accelaration = -500.0f;
	}
	else
	{
		m_Accelaration = 0.0f;
	}

	if(m_Position.m_X < 0.0f)
	{
		m_Position.m_X = 0.0f;
	}
	else if(m_Position.m_X + m_Dims.m_X > 1024.0f)
	{
		m_Position.m_X = 1024.0f - m_Dims.m_X;
	}

	m_Velocity += Vec2(m_Accelaration * deltaseconds, 0.0f);
	m_Velocity = m_Velocity * deltaseconds;

	Translate(m_Velocity);
}

void Paddle::Render()
{
	Renderer::GetInstance()->DrawQuad(m_Position, m_Dims, m_Color, APEX_DEFAULT_TEXTURE);
}

void Paddle::Translate(Vec2& translate)
{
	m_Position += translate;
}
