#include "App.h"

#include "Game.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Core/Logger.h"

App* g_App = nullptr;

extern Window* g_Window;

App::App()
{
}

App::~App()
{
}

void App::Startup()
{
	g_Window = new Window();
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
}

void App::Update(float deltaseconds)
{

}

void App::Render()
{
}

void App::EndFrame()
{
}

void App::Shutdown()
{
}

void App::UpdateFromInput()
{
}