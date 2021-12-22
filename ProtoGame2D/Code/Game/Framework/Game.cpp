#include "Game.h"

#include "Engine/Core/GameCommon.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/ShaderDefinition.h"
#include "Engine/Graphics/Buffers/FrameBuffer.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Input/WinKeys.h"

float x = 512.0f;
const Mat4 g_Camera = Mat4::orthographic(APEX_WINDOW_DIMS.m_X, APEX_WINDOW_DIMS.m_Y, APEX_WINDOW_DIMS.m_Z, APEX_WINDOW_DIMS.m_W, -2.0f, 2.0f);

extern InputSystem* g_InputSystem;

Game::Game()
{
	m_ShaderDef = new ShaderDefinition(*ShaderDefinition::InitializeDef(APEX_SHADER_XML));
	m_Shader = Renderer::GetInstance()->GetOrCreateShader(m_ShaderDef);
	
	m_ScreenShaderDef = new ShaderDefinition(*ShaderDefinition::InitializeDef(APEX_SCREENSHADER_XML));
	m_ScreenShader = Renderer::GetInstance()->GetOrCreateShader(m_ScreenShaderDef);
	
	Renderer::GetInstance()->EnableBlend(ParseBlendFac[m_Shader->GetSRC()], ParseBlendFac[m_Shader->GetDST()], ParseBlendOp[m_Shader->GetOP()]);

	m_SrcBuffer = new FrameBuffer();
	m_DestBuffer = new FrameBuffer();
}

Game::~Game()
{
	delete m_ShaderDef;
	m_ShaderDef = nullptr;
	
	delete m_Shader;
	m_Shader = nullptr;
	
	delete m_ScreenShaderDef;
	m_ScreenShaderDef = nullptr;
	
	delete m_ScreenShader;
	m_ScreenShader = nullptr;
	
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
	if(g_InputSystem->IsHeldDown(D))
	{
		x += 10.0f * deltaseconds;
	}
	else if(g_InputSystem->IsHeldDown(A))
	{
		x -= 10.0f * deltaseconds;
	}

	if(x >= 924.0f)
	{
		x = 924.0f;
	}
	else if( x <= 0.0f)
	{
		x = 0.0f;
	}
}

void Game::Render()
{
	m_SrcBuffer->Bind();

	Renderer::GetInstance()->ClearColor();
	Renderer::GetInstance()->Clear();

	m_Shader->Bind();

	m_Shader->SetUniformMat4f("u_Proj", g_Camera);

	Renderer::GetInstance()->DrawQuad(Vec2(x, 200.0f), Vec2(100.0f, 25.0f), Vec4(0.03f, 0.57f, 0.81f, 1.0f), APEX_DEFAULT_TEXTURE, *m_Shader);
	
	m_SrcBuffer->UnBind();

	Renderer::GetInstance()->CopyFrameBuffer(m_SrcBuffer, m_DestBuffer);
	Renderer::GetInstance()->DrawFrameBuffer(Vec2(APEX_WINDOW_DIMS.m_X, APEX_WINDOW_DIMS.m_Z), Vec2(APEX_WINDOW_DIMS.m_Y, APEX_WINDOW_DIMS.m_W));
}

void Game::EndFrame()
{
	Renderer::GetInstance()->SwappingBuffers();
}
