#include "Ball.h"

#include "GameCommon.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Engine/Core/EngineCommon.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Input/WinKeys.h"

extern InputSystem* g_InputSystem;

static Ball* m_Ball = nullptr;

Ball::Ball()
	: m_Translate(Vec2()), m_Velocity(Vec2()), m_Center(Vec2()), m_Radius(BB_BALL_RADIUS)
{
	//Entity();
	m_Position = Vec2(552.0f, 55.0f);
	m_Color = Color::GREEN;
	m_Center = m_Position;
}

Ball::~Ball()
{
}

void Ball::Update(float deltaseconds)
{
	if(!m_HasLaunched)
	{
		if(g_InputSystem->WasKeyJustPressed(SPACEBAR))
	    {
	    	m_Velocity = BB_BALL_VELOCITY;
			m_HasLaunched = true;
	    }

		if(g_InputSystem->GetMousePosition().m_X >= m_Dims.m_X / 2 && g_InputSystem->GetMousePosition().m_X <= APEX_WINDOW_DIMS[1] - m_Dims.m_X / 2)
	    {
	    	m_Position.m_X = g_InputSystem->GetMousePosition().m_X;
	    }
	    else if(g_InputSystem->GetMousePosition().m_X > APEX_WINDOW_DIMS[1] - m_Dims.m_X / 2)
	    {
	    	m_Position.m_X = APEX_WINDOW_DIMS[1];
	    }
	    else if(g_InputSystem->GetMousePosition().m_X < m_Dims.m_X / 2)
	    {
	    	m_Position.m_X = APEX_WINDOW_DIMS[0];
	    }
	}

	if(m_HasLaunched)
	{
		if(m_Position.m_X - m_Radius < APEX_WINDOW_DIMS[0] || m_Position.m_X + m_Radius > APEX_WINDOW_DIMS[1])
	    {
	    	m_Velocity.m_X *= -1;
	    }
	    
	    if(m_Position.m_Y + m_Radius > APEX_WINDOW_DIMS[3])
	    {
	    	m_Velocity.m_Y *= -1;
	    }
	}
	else
	{
		if(m_Position.m_X - 100.0f < APEX_WINDOW_DIMS[0])
	    {
	    	m_Position.m_X = 100.0f;
	    }
		else if(m_Position.m_X + 100.0f > APEX_WINDOW_DIMS[1])
		{
			m_Position.m_X = 924.0f;
		}
	}

	m_Translate += m_Velocity * deltaseconds;
	m_Translate = m_Translate * deltaseconds;

	Translate(m_Translate);
}

void Ball::Render()
{
	Renderer::GetInstance()->SetModelTranslation();
	Renderer::GetInstance()->DrawDisc(m_Position, m_Radius, m_Color);
}

void Ball::Translate(const Vec2& translate)
{
	m_Position += translate;
	m_Center = m_Position;
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
