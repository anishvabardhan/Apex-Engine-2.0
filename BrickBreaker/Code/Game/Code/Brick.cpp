#include "Brick.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Ball.h"
#include "Engine/Maths/MathUtils.h"

Brick::Brick()
{
	Entity();
	m_Position = Vec2(0.0f, 0.0f);
	m_Dims = BRICK_DIMS;
	m_Color = Color::WHITE;

	for(int i = 0; i < NUM_OF_ROWS; i++)
	{
		for(int j = 0; j < NUM_OF_COLS; j++)
		{
			m_IsDestroyed[i][j] = false;
		}
	}
}

Brick::Brick(const Vec2& position)
{
	Entity();
	m_Position = position;
	m_Dims = Vec2(124.0f, 48.0f);
	m_Color = Color::WHITE;

	for(int i = 0; i < NUM_OF_ROWS; i++)
	{
		for(int j = 0; j < NUM_OF_COLS; j++)
		{
			m_IsDestroyed[i][j] = false;
		}
	}
}

Brick::~Brick()
{
}

void Brick::Update(float deltaseconds)
{
	UNUSED(deltaseconds)
		
	float x = 0.0f;
	float y = 0.0f;

	for(int i = 0; i < NUM_OF_ROWS; i++)
	{
	 	y = BRICK_MAP_SPACE.m_Mins.m_Y + (m_Dims.m_Y) * i;
	 
	 	for(int j = 0; j < NUM_OF_COLS; j++)
	 	{
	 		x = BRICK_MAP_SPACE.m_Mins.m_X + (m_Dims.m_X) * j;
	 
	 		m_Position = Vec2(x, y);

			AABB2 bounds = AABB2(m_Position, m_Position + m_Dims);

	        if(Ball::GetInstance()->m_HasLaunched && !m_IsDestroyed[i][j])
	        {
				if(Disc_AABB2Collision(Ball::GetInstance()->m_Center, Ball::GetInstance()->m_Radius, bounds))
				{
					m_IsDestroyed[i][j] = true;

					Vec2 refPoint = bounds.GetNearestPoint( Ball::GetInstance()->m_Center );
				
		            Vec2 normal = ( Ball::GetInstance()->m_Center - refPoint ).GetNormalised();

		            Ball::GetInstance()->m_Velocity = Ball::GetInstance()->m_Velocity.Reflected( normal );
				}
	        }
	 	}
	}
}

void Brick::Render()
{
	float x = 0.0f;
	float y = 0.0f;

	for(int i = 0; i < NUM_OF_ROWS; i++)
	{
		 y = BRICK_MAP_SPACE.m_Mins.m_Y + (m_Dims.m_Y) * i;
		 
		 for(int j = 0; j < NUM_OF_COLS; j++)
		 {
			 if((i + j) % 2 == 0)
			 {
			 	m_Color = Color::YELLOW;
			 }
			 else
			 {
			 	m_Color = Color::RED;
			 }
		 	 x = BRICK_MAP_SPACE.m_Mins.m_X + (m_Dims.m_X) * j;
		 	 
		 	 m_Position = Vec2(x, y);
		     AABB2 aabb2(m_Position, m_Position + m_Dims);

			 Renderer::GetInstance()->SetModelTranslation();

	 	     if(!m_IsDestroyed[i][j])
	 	     {
	 	     	Renderer::GetInstance()->DrawAABB2(aabb2, m_Color);
	 	     }
		 }
	}
}
