#include "Game.h"

#include "Engine/Core/GameCommon.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/ShaderDefinition.h"
#include "Engine/Graphics/Buffers/FrameBuffer.h"

Game::Game()
{
	Renderer::CreateInstance();
	Renderer::GetInstance()->StartUp();

	m_ShaderDef = new ShaderDefinition(*ShaderDefinition::InitializeDef(SHADER_XML));
	m_Shader = new Shader(m_ShaderDef);
	
	m_ScreenShaderDef = new ShaderDefinition(*ShaderDefinition::InitializeDef(SCREENSHADER_XML));
	m_ScreenShader = Renderer::GetInstance()->GetOrCreateShader(m_ScreenShaderDef);
	
	Renderer::GetInstance()->EnableBlend(ParseBlendFac[m_Shader->GetSRC()], ParseBlendFac[m_Shader->GetDST()], ParseBlendOp[m_Shader->GetOP()]);

	m_CurrentBuffer = new FrameBuffer();
	m_NextBuffer = new FrameBuffer();
}

Game::~Game()
{
	Renderer::GetInstance()->ShutDown();
	Renderer::DestroyInstance();
}

void Game::BeginFrame()
{
	m_CurrentBuffer->Bind();

	Renderer::GetInstance()->ClearColor();
	Renderer::GetInstance()->Clear();

	m_Shader->Bind();

	Mat4 camera = Mat4::orthographic(WINDOW_DIMS.m_X, WINDOW_DIMS.m_Y, WINDOW_DIMS.m_Z, WINDOW_DIMS.m_W, -2.0f, 2.0f);

	m_Shader->SetUniformMat4f("u_Proj", camera);
}

void Game::Update()
{
}

void Game::Render()
{
		Renderer::GetInstance()->DrawQuad(Vec2(200.0f, 200.0f), Vec2(100.0f, 50.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f), "../Data/Textures/stripes.png", *m_Shader);
}

void Game::EndFrame()
{
	m_CurrentBuffer->UnBind();

	Renderer::GetInstance()->ClearColor();
	Renderer::GetInstance()->Clear();

	m_ScreenShader->Bind();

	Renderer::GetInstance()->CopyFrameBuffer(m_CurrentBuffer, m_NextBuffer);
	Renderer::GetInstance()->DrawFrameBuffer(Vec2(WINDOW_DIMS.m_X, WINDOW_DIMS.m_Z), Vec2(WINDOW_DIMS.m_Y, WINDOW_DIMS.m_W));

	Renderer::GetInstance()->SwappingBuffers();
}
