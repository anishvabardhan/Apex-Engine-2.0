#include "App.h"

#include "Game.h"
#include "Engine/Core/EngineCommon.h"
#include "Engine/Window/Window.h"
#include "Engine/Core/Time.h"
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
extern Renderer* g_Renderer;

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
	g_Window->Init("ProtoGame2D", CLIENT_DIMS);
	g_Window->SetInputSystem(g_InputSystem);

	LogStartup();
	
	g_Renderer = new Renderer();
	g_Renderer->StartUp();

	m_Time = new Time(60);

	m_Game = new Game();
}

void App::RunFrame()
{
	BeginFrame();
	Update(m_Time->GetTimeDelta());
	Render();
	EndFrame();
}

void App::BeginFrame()
{
	g_InputSystem->BeginFrame();

	g_Window->RunMessagePump();

	m_Time->Update();

	m_Game->BeginFrame();
}

void App::Update(float deltaseconds)
{
	if(m_IsSlowMo)
	{
		deltaseconds *= 0.25f;
	}

	if(m_IsPaused) {deltaseconds = 0.0f;}

	g_InputSystem->Update(deltaseconds);
	UpdateFromInput();

	m_Game->Update(deltaseconds);

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
	SAFE_DELETE_POINTER(m_Game)

	g_Renderer->ShutDown();
	SAFE_DELETE_POINTER(g_Renderer)

	LogShutdown();

	g_Window->Destroy();
	SAFE_DELETE_POINTER(g_Window)

	g_InputSystem->ShutDown();
	SAFE_DELETE_POINTER(g_InputSystem)

}

void App::UpdateFromInput()
{
	if(g_InputSystem->WasKeyJustPressed(ESCAPE))
	{
		g_Window->AppQuitting();
	}

	if(g_InputSystem->WasKeyJustPressed(Q))
	{
		m_Game->m_DebugDraw = !m_Game->m_DebugDraw;
	}

	if(g_InputSystem->IsHeldDown(S))
	{
		m_IsSlowMo = true;
	}
	else
	{
		m_IsSlowMo = false;
	}

	if(g_InputSystem->WasKeyJustPressed(P))
	{
		m_IsPaused = !m_IsPaused;
	}

	if(g_InputSystem->WasKeyJustPressed(R))
	{
		const std::wstring title = L"Apex Engine 2.0";

		g_Window->SetTitle(title);
	}
}