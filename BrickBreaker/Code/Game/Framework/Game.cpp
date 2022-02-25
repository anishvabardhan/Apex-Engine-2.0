#include "Game.h"

#include "Engine/Core/Color.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/Buffers/FrameBuffer.h"
#include "Engine/Window/Window.h"
#include "Engine/Core/EngineCommon.h"

// Declaring Engine Systems

extern InputSystem* g_InputSystem;
extern Window* g_Window;
extern Renderer* g_Renderer;
 
//--------------------------------------------------------------------------------------------------
// Creating a Camera

const Mat4 g_Camera = Mat4::Orthographic(APEX_WINDOW_DIMS[0], APEX_WINDOW_DIMS[1], APEX_WINDOW_DIMS[2], APEX_WINDOW_DIMS[3], -2.0f, 2.0f);

//--------------------------------------------------------------------------------------------------

Game::Game()
	:m_Paddle(Paddle(this)),
     m_Map(Map(this)),
     m_Ball(Ball(this))
{
	Random::SetSeed();
	
	g_Renderer->EnableBlend(ParseBlendFac[g_Renderer->GetDefaultShader()->GetSRC()], ParseBlendFac[g_Renderer->GetDefaultShader()->GetDST()], ParseBlendOp[g_Renderer->GetDefaultShader()->GetOP()]);

	m_SrcBuffer = new FrameBuffer(Vec2(APEX_WINDOW_DIMS[1], APEX_WINDOW_DIMS[3]));
}

Game::~Game() 
{
	SAFE_DELETE_POINTER(m_SrcBuffer)
}

//--------------------------------------------------------------------------------------------------
// Begin Frame function

void Game::BeginFrame()
{
}

//--------------------------------------------------------------------------------------------------
// Updates happening every frame

void Game::Update(float deltaseconds)
{
	m_Paddle.Update(deltaseconds);
	m_Map.Update(deltaseconds);
	m_Ball.Update(deltaseconds);
}

//--------------------------------------------------------------------------------------------------
// Rendering the frame

void Game::Render()
{
	m_SrcBuffer->Bind();

	g_Renderer->ClearColor();
	g_Renderer->Clear();

	g_Renderer->BindDefaultShader();

	g_Renderer->SetCameraUniform(g_Camera);

	m_Map.Render();
	m_Ball.Render();
	m_Paddle.Render();

	m_SrcBuffer->UnBind();

	g_Renderer->CopyFrameBuffer(m_SrcBuffer, nullptr);
}

//--------------------------------------------------------------------------------------------------
// Ending the frame

void Game::EndFrame()
{
	g_Renderer->SwappingBuffers();
}

//--------------------------------------------------------------------------------------------------