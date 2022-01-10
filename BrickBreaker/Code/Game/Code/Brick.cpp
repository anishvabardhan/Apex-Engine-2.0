#include "Brick.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Color.h"
#include "Ball.h"

Brick::Brick()
{
	Entity();
	m_Position = Vec2(0.0f, 0.0f);
	m_Dims = Vec2(124.0f, 48.0f);
	m_Color = Color::YELLOW;

	for(int i = 0; i < NUM_OF_BRICKS / 8; i++)
	{
		for(int j = 0; j < NUM_OF_BRICKS / 4; j++)
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
	m_Color = Color::YELLOW;
}

Brick::~Brick()
{
}

void Brick::Update(float deltaseconds)
{
	UNUSED(deltaseconds)
		
	float x = 0.0f;
	float y = 0.0f;

	for(int i = 0; i < NUM_OF_BRICKS / 8; i++)
	{
	 	y = BRICK_MAP_SPACE.m_Mins.m_Y + (m_Dims.m_Y + 4.0f) * i;
	 
	 	for(int j = 0; j < NUM_OF_BRICKS / 4; j++)
	 	{
	 		x = BRICK_MAP_SPACE.m_Mins.m_X + (m_Dims.m_X + 4.0f) * j;
	 
	 		m_Position = Vec2(x, y);

	        if(!m_IsDestroyed[i][j])
	        {
	        	if((Ball::GetInstance()->m_Position.m_Y < m_Position.m_Y + m_Dims.m_Y && Ball::GetInstance()->m_Position.m_Y + Ball::GetInstance()->m_Dims.m_Y > m_Position.m_Y) && (Ball::GetInstance()->m_Position.m_X > m_Position.m_X && Ball::GetInstance()->m_Position.m_X + Ball::GetInstance()->m_Dims.m_X < m_Position.m_X + m_Dims.m_X))
	            {
	            	Ball::GetInstance()->m_Velocity.m_Y *= -1;
	            	m_IsDestroyed[i][j] = true;
	            }
	        }

	        if(!m_IsDestroyed[i][j])
	        {
	        	if((Ball::GetInstance()->m_Position.m_X < m_Position.m_X + m_Dims.m_X && Ball::GetInstance()->m_Position.m_X + Ball::GetInstance()->m_Dims.m_X > m_Position.m_X) && (Ball::GetInstance()->m_Position.m_Y > m_Position.m_Y && Ball::GetInstance()->m_Position.m_Y + Ball::GetInstance()->m_Dims.m_Y < m_Position.m_Y + m_Dims.m_Y))
	            {
	                Ball::GetInstance()->m_Velocity.m_X *= -1;
	                m_IsDestroyed[i][j] = true;
	            }
	        }
	 	}
	}
}

void Brick::Render()
{
	float x = 0.0f;
	float y = 0.0f;

	for(int i = 0; i < NUM_OF_BRICKS / 8; i++)
	{
		 y = BRICK_MAP_SPACE.m_Mins.m_Y + (m_Dims.m_Y + 4.0f) * i;
		 
		 for(int j = 0; j < NUM_OF_BRICKS / 4; j++)
		 {
		 	 x = BRICK_MAP_SPACE.m_Mins.m_X + (m_Dims.m_X + 4.0f) * j;
		 	 
		 	 m_Position = Vec2(x, y);
	 	 
	 	     if(!m_IsDestroyed[i][j])
	 	     {
	 	     	Renderer::GetInstance()->DrawQuad(m_Position, m_Dims, m_Color, APEX_DEFAULT_TEXTURE);
	 	     }
		 }
	}
}
