#include "Paddle.h"

#include "Ball.h"
#include "GameCommon.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Engine/Core/EngineCommon.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Maths/MathUtils.h"

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

	AABB2 aabb2(m_Position, m_Position + m_Dims);

	if(Ball::GetInstance()->m_HasLaunched && Disc_AABB2Collision(Ball::GetInstance()->m_Center, Ball::GetInstance()->m_Radius, aabb2))
	{
		Vec2 refPoint = aabb2.GetNearestPoint( Ball::GetInstance()->m_Center );
		Vec2 normal = ( Ball::GetInstance()->m_Center - refPoint ).GetNormalised();

		float deviation = RangeMap(refPoint.m_X, m_Position.m_X, m_Position.m_X + m_Dims.m_X, -BB_PADDLE_DEVIATION_RANGE, BB_PADDLE_DEVIATION_RANGE);

		Ball::GetInstance()->m_Velocity = Ball::GetInstance()->m_Velocity.Reflected( normal );
		
		float angleDeviated = Ball::GetInstance()->m_Velocity.GetAngleDegrees() - deviation;

		Ball::GetInstance()->m_Velocity = Vec2::MakeFromPolarDegrees(angleDeviated, Ball::GetInstance()->m_Velocity.GetLength());
	}
}

void Paddle::Render()
{
	AABB2 aabb2(m_Position, m_Position + m_Dims);
	Renderer::GetInstance()->SetModelTranslation();
	Renderer::GetInstance()->DrawAABB2(aabb2, m_Color);
}