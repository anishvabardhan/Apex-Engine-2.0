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
	g_Window->SetInputSystem(g_InputSystem);

	Renderer::CreateInstance();

	LogStartup();
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
}

void App::Update(float deltaseconds)
{
	g_InputSystem->Update(deltaseconds);
	UpdateFromInput();
	g_InputSystem->EndFrame();
}

void App::Render()
{
}

void App::EndFrame()
{
}

void App::Shutdown()
{
	g_Window->Release();
	g_InputSystem->ShutDown();
}

void App::UpdateFromInput()
{
	if(g_InputSystem->WasKeyJustPressed(ESCAPE))
	{
		m_IsQuitting = true;
	}
}