#include "Ball.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Engine/Core/GameCommon.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Input/WinKeys.h"

extern InputSystem* g_InputSystem;

static Ball* m_Ball = nullptr;

Ball::Ball()
	: m_Velocity(Vec2(0.0f, 0.0f)), m_Translate(Vec2(0.0f, 0.0f))
{
	Entity();
	m_Position = Vec2(552.0f, 47.5f);
	m_Dims = Vec2(20.0f, 20.0f);
	m_Color = Color::GREEN;
	m_Center = Vec2(m_Position.m_X + (m_Dims.m_X / 2), m_Position.m_Y + (m_Dims.m_Y / 2));
	m_Radius = 10.0f;
}

Ball::~Ball()
{
}

void Ball::Update(float deltaseconds)
{
	if(g_InputSystem->WasKeyJustPressed(SPACEBAR))
	{
		m_Velocity = BB_BALL_VELOCITY;
	}
	else if(m_Velocity.m_Y == 0.0f)
	{
		if(g_InputSystem->IsHeldDown(D))
	    {
		    m_Velocity.m_X = BB_PADDLE_ACCELARATION;
	    }
	    else if(g_InputSystem->IsHeldDown(A))
	    {
		    m_Velocity.m_X = -BB_PADDLE_ACCELARATION;
	    }
	    else
	    {
		    m_Velocity.m_X = 0.0f;
	    }
	}

	if(m_Velocity.m_Y != 0.0f)
	{
		if(m_Position.m_X < APEX_WINDOW_DIMS[0] || m_Position.m_X + m_Dims.m_X > APEX_WINDOW_DIMS[1])
	    {
	    	m_Velocity.m_X *= -1;
	    }
	    
	    if(m_Position.m_Y < APEX_WINDOW_DIMS[2] || m_Position.m_Y + m_Dims.m_Y > APEX_WINDOW_DIMS[3])
	    {
	    	m_Velocity.m_Y *= -1;
	    }
	}
	else
	{
		if(m_Position.m_X - 90.0f < APEX_WINDOW_DIMS[0])
	    {
	    	m_Position.m_X = 90.0f;
	    }
		else if(m_Position.m_X + 110.0f > APEX_WINDOW_DIMS[1])
		{
			m_Position.m_X = 914.0f;
		}
	}

	m_Translate += m_Velocity * deltaseconds;
	m_Translate = m_Translate * deltaseconds;

	Translate(m_Translate);
}

void Ball::Render()
{
	Renderer::GetInstance()->DrawQuad(m_Position, m_Dims, m_Color, PROTOGAME2D_BALL_TEXTURE);
}

void Ball::Translate(const Vec2& translate)
{
	m_Position += translate;
}

void Ball::CreateInstance()
{
	m_Ball = new Ball();
}

Ball* Ball::GetInstance()
{
	return m_Ball;
}

void Ball::DestroyInstance()
{
	if(m_Ball)
	{
		delete m_Ball;
	    m_Ball = nullptr;
	}
}
