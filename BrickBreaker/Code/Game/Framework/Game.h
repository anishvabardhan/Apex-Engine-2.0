#pragma once

#include "Engine/Core/GameCommon.h"
#include "Game/Code/Brick.h"

class ShaderDefinition;
class FrameBuffer;
class Paddle;
class Brick;

class Game
{
	ShaderDefinition* m_ShaderDef = nullptr;
	FrameBuffer* m_SrcBuffer = nullptr;
	FrameBuffer* m_DestBuffer = nullptr;
    Paddle* m_Paddle = nullptr;
	Brick* m_Bricks = nullptr;

public:
	Game();
	~Game();

	void BeginFrame();
	void Update(float deltaseconds);
	void Render();
	void EndFrame();
};