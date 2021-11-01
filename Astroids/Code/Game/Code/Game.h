#pragma once

#include "Ship.h"
#include "Astroid.h"
#include "Bullet.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Time.h"

const int MAX_ASTEROIDS = 150;
const int MAX_BULLETS = 6;

class Game
{
	Window g_App;
	Time g_TS;
	Renderer* g_Renderer;
	Disc2D *g_PlayerDisc, *g_AstroidDisc[MAX_ASTEROIDS], *g_BulletDisc;
	Ship* g_Player;

	Astroid* g_Objects;
	Astroid* g_Astroid[MAX_ASTEROIDS];

	Bullet* g_Bullet;

	Vec2 g_Update;
	Vec2 g_Translate;
	Vec2 g_BulletVelocity;

	float g_BulletLife;

	bool g_IsFiring;

	int g_NumOfBullets;
	int g_NumOfAstroids;
public:
	Game();
	~Game();

	void BeginPlay();
	void Tick();

	void SpawnBullet();
	void DestroyBullet();

	void DestroyAstroid(int index);
};