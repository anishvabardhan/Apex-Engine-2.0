#include "App.h"

#include "Game.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Logger.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Input/WinKeys.h"

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

	LogStartup();
	
	Renderer::CreateInstance();
	Renderer::GetInstance()->StartUp();

	m_Game = new Game();
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

	m_Game->BeginFrame();
}

void App::Update(float deltaseconds)
{
	g_InputSystem->Update(deltaseconds);
	UpdateFromInput();

	m_Game->Update();

	g_InputSystem->EndFrame();
}

void App::Render()
{
	m_Game->Render();
}

void App::EndFrame()
{
	m_Game->EndFrame();

	m_IsQuitting = g_Window->IsAppQuiting();
}

void App::Shutdown()
{
	delete m_Game;
	m_Game = nullptr;
	
	Renderer::GetInstance()->ShutDown();
	Renderer::DestroyInstance();

	LogShutdown();

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
}