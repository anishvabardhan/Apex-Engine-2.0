#include "Map.h"

#include "GameCommon.h"
#include "Engine/Core/Color.h"
#include "Engine/Maths/MathUtils.h"
#include "Game/Framework/Game.h"
#include "Engine/Graphics/Renderer.h"

extern Renderer* g_Renderer;

Map::Map(Game* owner)
	:Entity(owner, Vec2::ZERO_ZERO, Vec2::ZERO_ZERO, Color::WHITE)
{
	for(int i = 0; i < BB_NUM_OF_ROWS; i++)
	{
		float y = BB_BRICK_MAP_SPACE.m_Mins.m_Y + (BB_BRICK_DIMS.m_Y) * i;

		for(int j = 0; j < BB_NUM_OF_COLS; j++)
		{
			m_Bricks[i][j] = new Brick(owner);
			m_IsBrickBallCollided[i][j] = false;

			if((i + j) % 2 == 0)
			{
				m_Bricks[i][j]->m_Color = Vec4(0.72f, 0.77f, 0.84f, 1.0f);
			}
			else
			{
				m_Bricks[i][j]->m_Color = Vec4(0.88f, 0.73f, 0.50f, 1.0f);
			}
 
			float x = BB_BRICK_MAP_SPACE.m_Mins.m_X + (BB_BRICK_DIMS.m_X) * j;
		 	 
		 	 m_Bricks[i][j]->m_Position = Vec2(x, y);
		}
	}
}

Map::~Map()
{
	for(int i = 0; i < BB_NUM_OF_ROWS; i++)
	{
		for(int j = 0; j < BB_NUM_OF_COLS; j++)
		{
			SAFE_DELETE_POINTER(m_Bricks[i][j])
		}
	}
}

void Map::Update(float deltaseconds)
{
	for(int i = 0; i < BB_NUM_OF_ROWS; i++)
	{
		for(int j = 0; j < BB_NUM_OF_COLS; j++)
		{
			m_Bricks[i][j]->Update(deltaseconds);
		}
	}

	BallBrickCollision();
	BallPaddleCollision();
}

void Map::Render()
{
	for(int i = 0; i < BB_NUM_OF_ROWS; i++)
	{
		for(int j = 0; j < BB_NUM_OF_COLS; j++)
		{
			m_Bricks[i][j]->Render();
		}
	}

	if(m_Owner->m_DebugDraw)
	{
		for(int i = 0; i < BB_NUM_OF_ROWS; i++)
	    {
	    	for(int j = 0; j < BB_NUM_OF_COLS; j++)
	    	{
	    		m_Bricks[i][j]->DebugRender();

			    if(m_IsBrickBallCollided[i][j])
	            {
			    	AABB2 aabb2(m_Bricks[i][j]->m_Position, m_Bricks[i][j]->m_Position + m_Bricks[i][j]->m_Dims);
	            	Vec2 refPoint = aabb2.GetNearestPoint( m_Owner->m_Ball.m_Position );
	            	Vec2 pos = m_Owner->m_Ball.m_Position;
	            	Vec2 normal = ( pos - refPoint ).GetNormalised();
	            	
	            	Vec2 start = Vec2::ZERO_ZERO;
	            	Vec2 end = normal * 100.0f;
	            	g_Renderer->SetModelTranslation(Mat4::Translation(Vec3(refPoint.m_X, refPoint.m_Y, 0.0f)));
	            	g_Renderer->DrawArrow(start, end, 3.0f, Color::YELLOW);

	            	m_IsBrickBallCollided[i][j] = false;
	            }
	    	}
	    }
	}
}

void Map::BallBrickCollision()
{
	for(int i = 0; i < BB_NUM_OF_ROWS; i++)
	{
	 	for(int j = 0; j < BB_NUM_OF_COLS; j++)
	 	{
			AABB2 bounds(m_Bricks[i][j]->m_Position, m_Bricks[i][j]->m_Position + m_Bricks[i][j]->m_Dims);
			
			if(m_Owner->m_Ball.m_HasLaunched && !m_Bricks[i][j]->m_IsDestroyed && Disc_AABB2Collision(m_Owner->m_Ball.m_Position, m_Owner->m_Ball.m_Radius, bounds))
			{
				m_IsBrickBallCollided[i][j] = true;

				m_Bricks[i][j]->m_IsDestroyed = true;

				Vec2 refPoint = bounds.GetNearestPoint( m_Owner->m_Ball.m_Position );

				Vec2 pos = m_Owner->m_Ball.m_Position;
		        Vec2 normal = ( pos - refPoint ).GetNormalised();

		        m_Owner->m_Ball.m_Velocity = m_Owner->m_Ball.m_Velocity.Reflected( normal );
			}
	 	}
	}
}

void Map::BallPaddleCollision()
{
	Vec2 min = m_Owner->m_Paddle.m_Position;
	Vec2 max = min + m_Owner->m_Paddle.m_Dims;
	AABB2 aabb2(min, max);

	if(m_Owner->m_Ball.m_HasLaunched && Disc_AABB2Collision(m_Owner->m_Ball.m_Position, m_Owner->m_Ball.m_Radius, aabb2))
	{
		m_Owner->m_IsPaddleBallCollision = true;

		Vec2 refPoint = aabb2.GetNearestPoint( m_Owner->m_Ball.m_Position );

		Vec2 pos = m_Owner->m_Ball.m_Position;
		Vec2 normal = ( pos - refPoint ).GetNormalised();

		float deviation = RangeMap(refPoint.m_X, m_Owner->m_Paddle.m_Position.m_X, m_Owner->m_Paddle.m_Position.m_X + m_Owner->m_Paddle.m_Dims.m_X, -BB_PADDLE_DEVIATION_RANGE, BB_PADDLE_DEVIATION_RANGE);

		m_Owner->m_Ball.m_Velocity = m_Owner->m_Ball.m_Velocity.Reflected( normal );

		float magnitude = m_Owner->m_Ball.m_Velocity.GetLength();
		magnitude *= 1.001f;

		float angleDeviated = m_Owner->m_Ball.m_Velocity.GetAngleDegrees() - deviation;

		m_Owner->m_Ball.m_Velocity = Vec2::MakeFromPolarDegrees(angleDeviated, magnitude);
	}
}