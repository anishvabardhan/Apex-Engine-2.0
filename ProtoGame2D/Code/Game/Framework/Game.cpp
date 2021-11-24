#include "Game.h"

#include "Engine/Core/GameCommon.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/ShaderDefinition.h"
#include "Engine/Graphics/Buffers/FrameBuffer.h"

Game::Game()
{
	m_ShaderDef = new ShaderDefinition(*ShaderDefinition::InitializeDef(APEX_SHADER_XML));
	m_Shader = Renderer::GetInstance()->GetOrCreateShader(m_ShaderDef);
	
	m_ScreenShaderDef = new ShaderDefinition(*ShaderDefinition::InitializeDef(APEX_SCREENSHADER_XML));
	m_ScreenShader = Renderer::GetInstance()->GetOrCreateShader(m_ScreenShaderDef);
	
	Renderer::GetInstance()->EnableBlend(ParseBlendFac[m_Shader->GetSRC()], ParseBlendFac[m_Shader->GetDST()], ParseBlendOp[m_Shader->GetOP()]);

	m_CurrentBuffer = new FrameBuffer();
	m_NextBuffer = new FrameBuffer();
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
	
	delete m_CurrentBuffer;
	m_CurrentBuffer = nullptr;
	
	delete m_NextBuffer;
	m_NextBuffer = nullptr;
}

void Game::BeginFrame()
{
	m_CurrentBuffer->Bind();

	Renderer::GetInstance()->ClearColor();
	Renderer::GetInstance()->Clear();

	m_Shader->Bind();

	Mat4 camera = Mat4::orthographic(APEX_WINDOW_DIMS.m_X, APEX_WINDOW_DIMS.m_Y, APEX_WINDOW_DIMS.m_Z, APEX_WINDOW_DIMS.m_W, -2.0f, 2.0f);

	m_Shader->SetUniformMat4f("u_Proj", camera);
}

void Game::Update()
{
}

void Game::Render()
{
		Renderer::GetInstance()->DrawQuad(Vec2(200.0f, 200.0f), Vec2(100.0f, 100.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), APEX_DEFAULT_TEXTURE, *m_Shader);
}

void Game::EndFrame()
{
	m_CurrentBuffer->UnBind();

	Renderer::GetInstance()->ClearColor();
	Renderer::GetInstance()->Clear();

	m_ScreenShader->Bind();

	Renderer::GetInstance()->CopyFrameBuffer(m_CurrentBuffer, m_NextBuffer);
	Renderer::GetInstance()->DrawFrameBuffer(Vec2(APEX_WINDOW_DIMS.m_X, APEX_WINDOW_DIMS.m_Z), Vec2(APEX_WINDOW_DIMS.m_Y, APEX_WINDOW_DIMS.m_W));

	Renderer::GetInstance()->SwappingBuffers();
}
