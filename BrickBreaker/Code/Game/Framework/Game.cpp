#include "Game.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/ShaderDefinition.h"
#include "Engine/Graphics/Buffers/FrameBuffer.h"
#include "Engine/Window/Window.h"

#include "Game/Code/Paddle.h"
#include "Game/Code/Ball.h"
#include "Game/Code/Brick.h"

#include <stdio.h>

#include "Engine/Core/Color.h"
#include "Engine/Maths/MathUtils.h"

// Declaring Engine Systems

extern InputSystem* g_InputSystem;
extern Shader* g_Shader;
extern Window* g_Window;

//--------------------------------------------------------------------------------------------------
// Creating a Camera

const Mat4 g_Camera = Mat4::Orthographic(APEX_WINDOW_DIMS[0], APEX_WINDOW_DIMS[1], APEX_WINDOW_DIMS[2], APEX_WINDOW_DIMS[3], -2.0f, 2.0f);

//--------------------------------------------------------------------------------------------------

Game::Game()
{
	Random::SetSeed();

	m_ShaderDef = Renderer::GetInstance()->GetOrCreateShaderDef(ShaderDefinition::InitializeDef(APEX_SHADER_XML));
	g_Shader = Renderer::GetInstance()->GetOrCreateShader(m_ShaderDef);
	
	Renderer::GetInstance()->EnableBlend(ParseBlendFac[g_Shader->GetSRC()], ParseBlendFac[g_Shader->GetDST()], ParseBlendOp[g_Shader->GetOP()]);

	m_SrcBuffer = new FrameBuffer(Vec2(1024.0f, 1024.0f));

	m_Paddle = new Paddle();
	m_Bricks = new Brick();
	Ball::CreateInstance();
}

Game::~Game() 
{
	Ball::DestroyInstance();

	delete m_Paddle;
	m_Paddle = nullptr;

	delete m_ShaderDef;
	m_ShaderDef = nullptr;
	
	delete g_Shader;
	g_Shader = nullptr;
	
	delete m_SrcBuffer;
	m_SrcBuffer = nullptr;
}

//--------------------------------------------------------------------------------------------------
// Begin Frame function

void Game::BeginFrame()
{
}

//--------------------------------------------------------------------------------------------------
// Updates happening every frame

void Game::Update(float deltaseconds)
{
	m_Paddle->Update(deltaseconds);
	m_Bricks->Update(deltaseconds);
	Ball::GetInstance()->Update(deltaseconds);

	AABB2 aabb2(m_Paddle->m_Position, m_Paddle->m_Position + m_Paddle->m_Dims);

	if(Ball::GetInstance()->m_Velocity.m_Y != 0.0f)
	{
		if(Ball::GetInstance()->m_Position.m_Y < 0.0f)
		{
			g_Window->AppQuitting();
		}
	}
}

//--------------------------------------------------------------------------------------------------
// Rendering the frame

void Game::Render()
{
	m_SrcBuffer->Bind();

	Renderer::GetInstance()->ClearColor();
	Renderer::GetInstance()->Clear();

	g_Shader->Bind();

	Renderer::GetInstance()->SetCameraUniform(g_Camera);

	m_Paddle->Render();
	m_Bricks->Render();
	Ball::GetInstance()->Render();

	m_SrcBuffer->UnBind();

	Renderer::GetInstance()->CopyFrameBuffer(m_SrcBuffer, nullptr);
}

//--------------------------------------------------------------------------------------------------
// Ending the frame

void Game::EndFrame()
{
	Renderer::GetInstance()->SwappingBuffers();
}

//--------------------------------------------------------------------------------------------------