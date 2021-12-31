#pragma once

class ShaderDefinition;
class FrameBuffer;
class Paddle;
class Ball;
class Brick;

class Game
{
	ShaderDefinition* m_ShaderDef = nullptr;
	FrameBuffer* m_SrcBuffer = nullptr;
	FrameBuffer* m_DestBuffer = nullptr;
    Paddle* m_Paddle;
    Ball* m_Ball;
    Brick* m_Brick;
public:
	Game();
	~Game();

	void BeginFrame();
	void Update(float deltaseconds);
	void Render();
	void EndFrame();
};