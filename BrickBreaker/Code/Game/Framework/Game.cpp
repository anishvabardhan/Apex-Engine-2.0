#include "Game.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/ShaderDefinition.h"
#include "Engine/Graphics/Buffers/FrameBuffer.h"
#include "Engine/Window/Window.h"

#include "Game/Code/Paddle.h"
#include "Game/Code/Ball.h"
#include "Game/Code/Brick.h"

extern InputSystem* g_InputSystem;
extern Shader* g_Shader;
extern Window* g_Window;

const Mat4 g_Camera = Mat4::orthographic(APEX_WINDOW_DIMS[0], APEX_WINDOW_DIMS[1], APEX_WINDOW_DIMS[2], APEX_WINDOW_DIMS[3], -2.0f, 2.0f);

Game::Game()
{
	Random::SetSeed();

	m_ShaderDef = Renderer::GetInstance()->GetOrCreateShaderDef(ShaderDefinition::InitializeDef(APEX_SHADER_XML));
	g_Shader = Renderer::GetInstance()->GetOrCreateShader(m_ShaderDef);
	
	Renderer::GetInstance()->EnableBlend(ParseBlendFac[g_Shader->GetSRC()], ParseBlendFac[g_Shader->GetDST()], ParseBlendOp[g_Shader->GetOP()]);

	m_SrcBuffer = new FrameBuffer();
	m_DestBuffer = new FrameBuffer();

	m_Paddle = new Paddle();
	Ball::CreateInstance();
	m_Bricks = new Brick();
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
	
	delete m_DestBuffer;
	m_DestBuffer = nullptr;
}

void Game::BeginFrame()
{
}

void Game::Update(float deltaseconds)
{
	if(Ball::GetInstance()->m_Velocity.m_Y != 0.0f)
	{
		if(Ball::GetInstance()->m_Position.m_X > m_Paddle->m_Position.m_X && Ball::GetInstance()->m_Position.m_X + Ball::GetInstance()->m_Dims.m_X < m_Paddle->m_Position.m_X + m_Paddle->m_Dims.m_X)
	    {
	    	if((Ball::GetInstance()->m_Center.m_Y - (m_Paddle->m_Position.m_Y + m_Paddle->m_Dims.m_Y)) * (Ball::GetInstance()->m_Center.m_Y - (m_Paddle->m_Position.m_Y + m_Paddle->m_Dims.m_Y)) < Ball::GetInstance()->m_Radius * Ball::GetInstance()->m_Radius)
	        {
	        	Ball::GetInstance()->m_Velocity.m_Y *= -1;

				Ball::GetInstance()->m_Velocity.m_X = -500.0f * sin((Ball::GetInstance()->m_Position.m_X + (Ball::GetInstance()->m_Dims.m_X * 0.5f)) - (m_Paddle->m_Position.m_X + (m_Paddle->m_Dims.m_X * 0.5f)));
	        }
	    }
		
		if(Ball::GetInstance()->m_Position.m_Y < 0.0f)
		{
			g_Window->AppQuitting();
		}
	}

	m_Paddle->Update(deltaseconds);
	Ball::GetInstance()->Update(deltaseconds);
	m_Bricks->Update(deltaseconds);
}

void Game::Render()
{
	m_SrcBuffer->Bind();

	Renderer::GetInstance()->ClearColor();
	Renderer::GetInstance()->Clear();

	g_Shader->Bind();

	g_Shader->SetUniformMat4f("u_Proj", g_Camera);

	Ball::GetInstance()->Render();
	m_Paddle->Render();
	m_Bricks->Render();

	m_SrcBuffer->UnBind();

	Renderer::GetInstance()->CopyFrameBuffer(m_SrcBuffer, m_DestBuffer);
	Renderer::GetInstance()->DrawFullScreenQuad();
}

void Game::EndFrame()
{
	Renderer::GetInstance()->SwappingBuffers();
}
