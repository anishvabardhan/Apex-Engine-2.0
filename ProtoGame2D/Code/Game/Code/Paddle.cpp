#include "Paddle.h"

#include "Engine/Core/CoreIncludes.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Shader.h"

Paddle* g_Paddle = nullptr;

Paddle::Paddle()
{
}

Paddle::~Paddle()
{
}

void Paddle::Update(float deltaseconds)
{
	UNUSED(deltaseconds)
}

void Paddle::Render(Shader shader)
{
	Renderer::GetInstance()->DrawQuad(Vec2(200.0f, 200.0f), Vec2(100.0f, 50.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), "../Data/Textures/stripes.png" , shader);
}
