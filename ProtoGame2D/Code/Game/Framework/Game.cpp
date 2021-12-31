#include "Game.h"

#include "Engine/Core/GameCommon.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/ShaderDefinition.h"
#include "Engine/Graphics/Buffers/FrameBuffer.h"
#include "Game/Code/Paddle.h"
#include "Game/Code/Ball.h"
#include "Engine/Window/Window.h"

extern InputSystem* g_InputSystem;
extern Shader* g_Shader;
extern Window* g_Window;

const Mat4 g_Camera = Mat4::orthographic(APEX_WINDOW_DIMS[0], APEX_WINDOW_DIMS[1], APEX_WINDOW_DIMS[2], APEX_WINDOW_DIMS[3], -2.0f, 2.0f);

Game::Game()
{
	m_ShaderDef = Renderer::GetInstance()->GetOrCreateShaderDef(ShaderDefinition::InitializeDef(APEX_SHADER_XML));
	g_Shader = Renderer::GetInstance()->GetOrCreateShader(m_ShaderDef);
	
	Renderer::GetInstance()->EnableBlend(ParseBlendFac[g_Shader->GetSRC()], ParseBlendFac[g_Shader->GetDST()], ParseBlendOp[g_Shader->GetOP()]);

	m_SrcBuffer = new FrameBuffer();
	m_DestBuffer = new FrameBuffer();

	m_Paddle = new Paddle();
	m_Ball = new Ball();
}

Game::~Game()
{
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
	if(m_Ball->m_Accelaration.m_Y != 0.0f)
	{
		if(m_Ball->m_Position.m_X > m_Paddle->m_Position.m_X && m_Ball->m_Position.m_X + m_Ball->m_Dims.m_X < m_Paddle->m_Position.m_X + m_Paddle->m_Dims.m_X)
	    {
	    	if(m_Ball->m_Position.m_Y < m_Paddle->m_Position.m_Y + m_Paddle->m_Dims.m_Y)
	        {
	        	m_Ball->m_Accelaration.m_Y *= -1;
	        }
	    }
		
		if(m_Ball->m_Position.m_Y < m_Paddle->m_Position.m_Y)
		{
			g_Window->AppQuitting();
		}
	}

	m_Paddle->Update(deltaseconds);
	m_Ball->Update(deltaseconds);
}

void Game::Render()
{
	m_SrcBuffer->Bind();

	Renderer::GetInstance()->ClearColor();
	Renderer::GetInstance()->Clear();

	g_Shader->Bind();

	g_Shader->SetUniformMat4f("u_Proj", g_Camera);

	m_Ball->Render();
	m_Paddle->Render();

	m_SrcBuffer->UnBind();

	Renderer::GetInstance()->CopyFrameBuffer(m_SrcBuffer, m_DestBuffer);
	Renderer::GetInstance()->DrawFullScreenQuad();
}

void Game::EndFrame()
{
	Renderer::GetInstance()->SwappingBuffers();
}
