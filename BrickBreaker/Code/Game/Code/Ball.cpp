#include "Ball.h"

#include "GameCommon.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Engine/Core/EngineCommon.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Input/WinKeys.h"
#include "Engine/Maths/MathUtils.h"
#include "Game/Framework/Game.h"

extern InputSystem* g_InputSystem;
extern Renderer* g_Renderer;

Ball::Ball(Game* owner)
	: Entity(owner, BB_BALL_POSITION, Vec2::ZERO_ZERO, Color::BLUE),
      m_Velocity(Vec2::ZERO_ZERO),
      m_Radius(BB_BALL_RADIUS)
{
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
	    
	    if(m_Position.m_Y - m_Radius < APEX_WINDOW_DIMS[0] || m_Position.m_Y + m_Radius > APEX_WINDOW_DIMS[3])
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

	Vec2 velocity = Vec2(Clamp(m_Velocity.m_X, BB_BALL_MIN_VELOCITY, BB_BALL_MAX_VELOCITY), Clamp(m_Velocity.m_Y, BB_BALL_MIN_VELOCITY, BB_BALL_MAX_VELOCITY));
	
	Translate(velocity * deltaseconds);
}

void Ball::Render()
{
	g_Renderer->SetModelTranslation();
	g_Renderer->DrawDisc(m_Position, m_Radius, m_Color);
	
	if(m_Owner->m_DebugDraw)
	{
		DebugRender();
	}
}

void Ball::DebugRender()
{
	g_Renderer->SetModelTranslation();
	g_Renderer->DrawRing(m_Position, m_Radius, Color::MAGENTA);

	Vec2 start = Vec2::ZERO_ZERO;
	Vec2 end = m_Velocity * 0.5f;
	g_Renderer->SetModelTranslation(Mat4::Translation(Vec3(m_Position.m_X, m_Position.m_Y, 0.0f)));
	g_Renderer->DrawArrow(start, end, 3.0f, Color::CYAN);
}

void Ball::Translate(const Vec2& translate)
{
	m_Position += translate;
}