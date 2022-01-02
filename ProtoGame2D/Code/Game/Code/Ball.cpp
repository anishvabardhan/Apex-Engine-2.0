#include "Ball.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Engine/Core/GameCommon.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Input/WinKeys.h"

extern InputSystem* g_InputSystem;

Ball::Ball()
	: m_Accelaration(Vec2(0.0f, 0.0f)), m_Velocity(Vec2(0.0f, 0.0f))
{
	Entity();
	m_Position = Vec2(502.0f, 47.5f);
	m_Dims = Vec2(20.0f, 20.0f);
	m_Color = Color::GREEN;
}

Ball::~Ball()
{
}

void Ball::Update(float deltaseconds)
{
	if(g_InputSystem->WasKeyJustPressed(SPACEBAR))
	{
		m_Accelaration = Vec2(-550.0f, 2000.0f);
	}
	else if(m_Accelaration.m_Y == 0.0f)
	{
		if(g_InputSystem->IsHeldDown(D))
	    {
		    m_Accelaration.m_X = 1500.0f;
	    }
	    else if(g_InputSystem->IsHeldDown(A))
	    {
		    m_Accelaration.m_X = -1500.0f;
	    }
	    else
	    {
		    m_Accelaration.m_X = 0.0f;
	    }
	}

	if(m_Accelaration.m_Y != 0.0f)
	{
		if(m_Position.m_X < 0.0f || m_Position.m_X + m_Dims.m_X > 1024.0f)
	    {
	    	m_Accelaration.m_X *= -1;
	    }
	    
	    if(m_Position.m_Y < 0.0f || m_Position.m_Y + m_Dims.m_Y > 1024.0f)
	    {
	    	m_Accelaration.m_Y *= -1;
	    }
	}
	else
	{
		if(m_Position.m_X - 40.0f < 0.0f)
	    {
	    	m_Position.m_X = 40.0f;
	    }
		else if(m_Position.m_X + 60.0f > 1024.0f)
		{
			m_Position.m_X = 964.0f;
		}
	}

	m_Velocity += m_Accelaration * deltaseconds;
	m_Velocity = m_Velocity * deltaseconds;

	Translate(m_Velocity);
}

void Ball::Render()
{
	Renderer::GetInstance()->DrawQuad(m_Position, m_Dims, m_Color, APEX_DEFAULT_TEXTURE);
}

void Ball::Translate(Vec2& translate)
{
	m_Position += translate;
}
