#include "Game.h"

#include "Engine/Maths/Random.h"
#include "Engine/Core/DebugSystem.h"

Random random(100, 500);

Game::Game()
	:g_TS(60), g_BulletVelocity(Vec2(7.5f, 7.5f)), g_Renderer(nullptr), g_BulletDisc(nullptr), g_Player(nullptr), g_Objects(nullptr), g_PlayerDisc(nullptr), g_NumOfBullets(0), g_NumOfAstroids(6), g_BulletLife(50.0f), g_IsFiring(false)
{
	for (int i = 0; i < g_NumOfAstroids; i++)
	{
		g_Astroid[i] = nullptr;
		g_AstroidDisc[i] = nullptr;
	}

	g_Bullet = nullptr;
}

Game::~Game()
{
	delete g_Player;
	delete g_Renderer;
}

void Game::BeginPlay()
{
	g_TS.SetSeed();
	
	//------------------------------------------------------------------------------------------------------
	//Instatntiating the characters 
	
	g_Player = new Ship((Vec2(30.0f, 30.0f)));

	g_Bullet = new Bullet(g_Translate);

	for (int i = 0; i < g_NumOfAstroids; i++)
	{	
		g_Objects = new Astroid(Vec2(Random::GetRandomFloatInRange(75.0f, 275.0f), Random::GetRandomFloatInRange(175.0f, 375.0f)), Vec2(random.GetRandomInRange(), random.GetRandomInRange()), 30.0f, 55.0f);

		g_Astroid[i] = g_Objects;

		g_AstroidDisc[i] = new Disc2D(g_Astroid[i]->GetPosition() + g_Astroid[i]->GetTranslate(), g_Astroid[i]->GetRadius());
	}
}

void Game::Tick()
{
	if (g_App.Init())
	{
		//--------------------------------------------------------------------------------------------------
		//GAME LOOP
	
		while (g_App.IsRun())
		{
			g_App.Broadcast();

			g_TS.Update();

			//----------------------------------------------------------------------------------------------
			//Initializing the renderer

			g_Renderer->InitRender();

			if (g_Bullet != nullptr)
			{
				g_BulletDisc = new Disc2D(g_Bullet->GetPosition() + g_Update, g_Bullet->m_Radius);
			}
			g_Renderer->Push();

			if (g_App.GetKey[SPACEBAR])
			{
				SpawnBullet();
			}

			if (g_IsFiring)
			{
				g_Update += g_BulletVelocity;

				g_Bullet->OnUpdate(g_Update, g_TS.GetTimeDelta());

				g_Bullet->Render();
			}
			else
			{
				g_Translate = g_Player->GetPosition() + g_Player->GetNosePosition() + g_Player->GetTranslate();
			}

			if (g_Bullet != nullptr && g_Bullet->GetAge() > g_BulletLife)
			{
				DestroyBullet();
			}

			g_Renderer->Pop();

			//----------------------------------------------------------------------------------------------
			//Rendering the player

				//------------------------------------------------------------------------------------------
				//Applying the collision discs on the entity

			if(g_Player != nullptr)
				g_PlayerDisc = new Disc2D(g_Player->GetPosition() + g_Player->GetTranslate(), 15.0f);

			g_Renderer->Push();

			g_Player->OnUpdate(g_TS.GetTimeDelta());

			g_Player->Render();

			DebugSystem::DebugCircle(g_PlayerDisc->GetRadius());
			DebugSystem::DebugLine();

			g_Renderer->Pop();

			//----------------------------------------------------------------------------------------------
			//Rendering the astroids

			for (int i = 0; i < g_NumOfAstroids; i++)
			{
				//------------------------------------------------------------------------------------------
				//Applying the collision discs on the entity

				if (g_Astroid[i] != nullptr)
				{
					g_AstroidDisc[i] = new Disc2D(g_Astroid[i]->GetPosition() + g_Astroid[i]->GetTranslate(), g_Astroid[i]->GetRadius());

					g_Renderer->Push();

					g_Astroid[i]->OnUpdate(g_TS.GetTimeDelta());

					g_Astroid[i]->Render();

					DebugSystem::DebugCircle(g_AstroidDisc[i]->GetRadius());

					g_Renderer->Pop();

					//------------------------------------------------------------------------------------------
					//Collision Detection

					if (Disc2D::CheckCollision(g_AstroidDisc[i], g_PlayerDisc))
					{
						delete g_Player;
						g_Player = new Ship((Vec2(30.0f, 30.0f)));
					}

					for (int j = 0; j < g_NumOfAstroids; j++)
					{
						if (g_Bullet != nullptr && g_Astroid[j] != nullptr && g_AstroidDisc[j] != nullptr)
						{
							if (Disc2D::CheckCollision(g_BulletDisc, g_AstroidDisc[j]))
							{
								DestroyAstroid(j);
								DestroyBullet();
							}
						}
					}

					//------------------------------------------------------------------------------------------
					//Deleting Heap Allocated Memory
				}
			}

			//----------------------------------------------------------------------------------------------
			/*Guarantee that all OpenGL commands
			made up to that point will complete
			executions in a finite amount time*/

			g_Renderer->Flush();

			//----------------------------------------------------------------------------------------------
			//Deleting Heap Allocated Memory

			delete g_PlayerDisc;

			//----------------------------------------------------------------------------------------------
			//Swapping front and back buffers each frame

			g_App.SwappingBuffers();
		}
	}
}

void Game::SpawnBullet()
{
	g_IsFiring = true;

	Vec2 forwardDir = g_Player->GetNosePosition().GetNormalised();

	g_BulletVelocity = Vec2(6.5f, 6.5f);

	g_BulletVelocity *= forwardDir * g_TS.GetTimeDelta();

	g_Bullet = new Bullet(g_Translate);
}

void Game::DestroyBullet()
{
	delete g_Bullet;
	g_Bullet = nullptr;
	g_Update = Vec2(0.0f, 0.0f);
	g_IsFiring = false;
}

void Game::DestroyAstroid(int index)
{
	Vec2 newPosition = g_Astroid[index]->GetPosition();
	Vec2 newTranslate = g_Astroid[index]->GetTranslate();
	float newMin = g_Astroid[index]->m_Min / 2;
	float newMax = g_Astroid[index]->m_Max / 2;

	if (newMin < 15.0f)
	{
		newMin = 0.0f;
		newMax = 0.0f;
	}

	if (index == g_NumOfAstroids - 1)
	{
		g_NumOfAstroids++;
		delete (g_Astroid[index]);
		delete g_AstroidDisc[index];
		g_Astroid[index] = new Astroid(newPosition, newTranslate, newMin, newMax);
		g_AstroidDisc[index] = new Disc2D(newPosition, newMin);
		g_Astroid[index + 1] = new Astroid(newPosition, newTranslate, newMin, newMax);
		g_AstroidDisc[index + 1] = new Disc2D(newPosition, newMin);
	}
	else
	{
		delete(g_Astroid[index]);
		g_Astroid[index] = nullptr;
		for (int j = index + 1; g_Astroid[j] != nullptr; j++)
		{
			g_Astroid[j - 1] = g_Astroid[j];
			g_Astroid[j] = nullptr;
		}
		g_NumOfAstroids++;
		g_Astroid[g_NumOfAstroids - 2] = new Astroid(newPosition, newTranslate, newMin, newMax);
		g_Astroid[g_NumOfAstroids - 1] = new Astroid(newPosition, newTranslate, newMin, newMax);

		delete(g_AstroidDisc[index]);
		g_AstroidDisc[index] = nullptr;
		for (int j = index + 1; g_AstroidDisc[j] != nullptr; j++)
		{
			g_AstroidDisc[j - 1] = g_AstroidDisc[j];
			g_AstroidDisc[j] = nullptr;
		}
		g_AstroidDisc[g_NumOfAstroids - 2] = new Disc2D(newPosition, newMin);
		g_AstroidDisc[g_NumOfAstroids - 1] = new Disc2D(newPosition, newMin);
	}

}