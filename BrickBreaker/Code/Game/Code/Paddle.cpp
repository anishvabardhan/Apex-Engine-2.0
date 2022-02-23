#include "Paddle.h"

#include "Ball.h"
#include "GameCommon.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Engine/Core/EngineCommon.h"
#include "Engine/Input/InputSystem.h"
#include "Game/Framework/Game.h"

extern InputSystem* g_InputSystem;
extern Renderer* g_Renderer;

Paddle::Paddle(Game* owner)
	: Entity(owner, BB_PADDLE_POSITION, BB_PADDLE_DIMS, Color::WHITE), m_Accelaration(0.0f), m_Velocity(Vec2(0.0f, 0.0f))
{
}

Paddle::~Paddle()
{
}

void Paddle::Update(float deltaseconds)
{
	UNUSED(deltaseconds);

	if(g_InputSystem->GetMousePosition().m_X >= m_Dims.m_X / 2 && g_InputSystem->GetMousePosition().m_X <= APEX_WINDOW_DIMS[1] - m_Dims.m_X / 2)
	{
		m_Position.m_X = g_InputSystem->GetMousePosition().m_X - m_Dims.m_X / 2;
	}
	else if(g_InputSystem->GetMousePosition().m_X > APEX_WINDOW_DIMS[1] - m_Dims.m_X / 2)
	{
		m_Position.m_X = APEX_WINDOW_DIMS[1] - m_Dims.m_X;
	}
	else if(g_InputSystem->GetMousePosition().m_X < m_Dims.m_X / 2)
	{
		m_Position.m_X = APEX_WINDOW_DIMS[0];
	}
}

void Paddle::Render()
{
	AABB2 aabb2(m_Position, m_Position + m_Dims);
	g_Renderer->SetModelTranslation();
	g_Renderer->DrawAABB2(aabb2, m_Color);

	if(m_Owner->m_DebugDraw)
	{
		 DebugRender();
	}
}

void Paddle::DebugRender()
{
    AABB2 aabb2(m_Position, m_Position + m_Dims);
    g_Renderer->SetModelTranslation();
    g_Renderer->DrawHollowAABB2(aabb2, 5.0f, Color::MAGENTA);

	if(m_Owner->m_IsPaddleBallCollision)
	{
		Vec2 refPoint = aabb2.GetNearestPoint( m_Owner->m_Ball.m_Position );
		Vec2 pos = m_Owner->m_Ball.m_Position;
		Vec2 normal = ( pos - refPoint ).GetNormalised();
		
		Vec2 start = Vec2::ZERO_ZERO;
		Vec2 end = normal * 100.0f;
		g_Renderer->SetModelTranslation(Mat4::Translation(Vec3(refPoint.m_X, refPoint.m_Y, 0.0f)));
		g_Renderer->DrawArrow(start, end, 3.0f, Color::YELLOW);

		m_Owner->m_IsPaddleBallCollision = false;
	}
}