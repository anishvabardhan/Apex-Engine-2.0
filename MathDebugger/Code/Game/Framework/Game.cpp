#include "Game.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/ShaderDefinition.h"
#include "Engine/Graphics/Buffers/FrameBuffer.h"
#include "Engine/Window/Window.h"

#include <stdio.h>

#include "Engine/Core/Color.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Maths/MathUtils.h"

// Declaring Engine Systems

extern InputSystem* g_InputSystem;
extern Shader* g_Shader;
extern Window* g_Window;

//--------------------------------------------------------------------------------------------------
// Creating a Camera

const Mat4 g_Camera = Mat4::Orthographic(APEX_WINDOW_DIMS[0], APEX_WINDOW_DIMS[1], APEX_WINDOW_DIMS[2], APEX_WINDOW_DIMS[3], -2.0f, 2.0f);

//--------------------------------------------------------------------------------------------------

Game::Game()
{
	Random::SetSeed();

	m_ShaderDef = Renderer::GetInstance()->GetOrCreateShaderDef(ShaderDefinition::InitializeDef(APEX_SHADER_XML));
	g_Shader = Renderer::GetInstance()->GetOrCreateShader(m_ShaderDef);
	
	Renderer::GetInstance()->EnableBlend(ParseBlendFac[g_Shader->GetSRC()], ParseBlendFac[g_Shader->GetDST()], ParseBlendOp[g_Shader->GetOP()]);

	Renderer::GetInstance()->InitRender();

	m_SrcBuffer = new FrameBuffer(Vec2(1024.0f, 1024.0f));

	m_AABB2 = AABB2::CENTER_PIVOT_AABB;
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

//--------------------------------------------------------------------------------------------------
// Begin Frame function

void Game::BeginFrame()
{
}

//--------------------------------------------------------------------------------------------------
// Updates happening every frame

void Game::Update(float deltaseconds)
{
}

//--------------------------------------------------------------------------------------------------
// Rendering the frame

void Game::Render()
{
	m_SrcBuffer->Bind();

	Renderer::GetInstance()->ClearColor();
	Renderer::GetInstance()->Clear();

	g_Shader->Bind();

	AABB2 aabb2(Vec2(400.0f, 400.0f), Vec2(600.0f, 600.0f));

	Renderer::GetInstance()->SetCameraUniform(g_Camera);

	Renderer::GetInstance()->BindTexture(Renderer::GetInstance()->GetDefaultTexture(), 0);

	Renderer::GetInstance()->SetModelTranslation();
	Renderer::GetInstance()->DrawAABB2(aabb2, Vec4(0.0f, 1.0f, 0.0f, 1.0f));

	Vec2 temp = aabb2.GetNearestPoint(g_InputSystem->GetMousePosition());
	Vec2 start = temp;
	Vec2 end = g_InputSystem->GetMousePosition();
	
	Renderer::GetInstance()->SetModelTranslation();
	Renderer::GetInstance()->DrawArrow(start, end, 5.0f, Vec4(1.0f, 0.0f, 0.0f, 1.0f));

	Renderer::GetInstance()->SetModelTranslation();
	Renderer::GetInstance()->DrawDisc(g_InputSystem->GetMousePosition(), 10.0f, Vec4(0.0f, 0.0f, 1.0f, 1.0f));

	if(Disc_AABB2Collision(end, 10.0f, aabb2))
	{
	    Renderer::GetInstance()->SetModelTranslation();
	    Renderer::GetInstance()->DrawDisc(Vec2(800.0f, 800.0f), 20.0f, Vec4(0.5f, 0.5f, 0.5f, 1.0f));
	}

	m_SrcBuffer->UnBind();

	Renderer::GetInstance()->CopyFrameBuffer(m_SrcBuffer, nullptr);
}

//--------------------------------------------------------------------------------------------------
// Ending the frame

void Game::EndFrame()
{
	Renderer::GetInstance()->SwappingBuffers();
}

//--------------------------------------------------------------------------------------------------