#include "App.h"

#include "Game.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Logger.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Input/WinKeys.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/ShaderDefinition.h"
#include "Engine/Graphics/Buffers/FrameBuffer.h"

#ifndef UNUSED
#define UNUSED(x) (void)x;
#endif

App* g_App = nullptr;

extern Window* g_Window;
extern InputSystem* g_InputSystem;

App::App()
{
}

App::~App()
{
}

void App::Startup()
{
	g_InputSystem = new InputSystem();
	g_InputSystem->Startup();

	g_Window = new Window();
	g_Window->Init("ProtoGame2D");
	g_Window->SetInputSystem(g_InputSystem);

	Renderer::CreateInstance();
	Renderer::GetInstance()->StartUp();

	LogStartup();

	m_ShaderDef = new ShaderDefinition(*ShaderDefinition::InitializeDef("Data/Materials/shader.xml"));
	m_Shader = Renderer::GetInstance()->GetOrCreateShader(m_ShaderDef);

	m_ScreenShaderDef = new ShaderDefinition(*ShaderDefinition::InitializeDef("Data/Materials/screenShader.xml"));
	m_ScreenShader = Renderer::GetInstance()->GetOrCreateShader(m_ScreenShaderDef);

	Renderer::GetInstance()->EnableBlend(ParseBlendFac[m_Shader->GetSRC()], ParseBlendFac[m_Shader->GetDST()], ParseBlendOp[m_Shader->GetOP()]);

	m_CurrentBuffer = new FrameBuffer();
	m_NextBuffer = new FrameBuffer();
}

void App::RunFrame()
{
	BeginFrame();
	Update(0.0f);
	Render();
	EndFrame();
}

void App::BeginFrame()
{
	g_InputSystem->BeginFrame();

	g_Window->RunMessagePump();

	m_CurrentBuffer->Bind();

	Renderer::GetInstance()->ClearColor();
	Renderer::GetInstance()->Clear();

	m_Shader->Bind();

	m_Shader->SetUniformMat4f("u_Proj", Mat4::orthographic(0.0f, 1024.0f, 0.0f, 1024.0f, -2.0f, 2.0f));
}

void App::Update(float deltaseconds)
{
	g_InputSystem->Update(deltaseconds);
	UpdateFromInput();
	g_InputSystem->EndFrame();

	Renderer::GetInstance()->SwappingBuffers();
}

void App::Render()
{
}

void App::EndFrame()
{
	m_IsQuitting = g_Window->IsAppQuiting();
}

void App::Shutdown()
{
	LogShutdown();

	Renderer::GetInstance()->ShutDown();
	Renderer::DestroyInstance();

	g_Window->Destroy();
	delete g_Window;
	g_Window = nullptr;

	g_InputSystem->ShutDown();
	delete g_InputSystem;
	g_InputSystem = nullptr;
}

void App::UpdateFromInput()
{
	if(g_InputSystem->WasKeyJustPressed(ESCAPE))
	{
		g_Window->AppQuitting();
	}

	if(g_InputSystem->WasKeyJustPressed(R))
	{
		const std::wstring title = L"Apex Engine 2.0";

		g_Window->SetTitle(title);
	}

	if (g_InputSystem->WasKeyJustPressed(SPACEBAR))
	{
	}
}