#include "DebugSystem.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphics/GLFunctions.h"

DebugSystem::DebugSystem()
{
}

DebugSystem::~DebugSystem()
{
}

void DebugSystem::DebugCircle(float scale)
{

	if (Window::GetInstance()->GetKey[F1])
	{
		GLfloat twicePi = 2.0f * (GLfloat)M_PI;

		Renderer::BeginLineLoop();

		glColor3f(0.0f, 1.0f, 0.0f);

		for (int i = 0; i < 100; i ++)
		{
			glVertex3f((scale * cos(i * twicePi / 100)), (scale * sin(i * twicePi / 100)), 0.0f);
		}

		Renderer::End();
	}

}

void DebugSystem::DebugLine()
{
	float vertices[6] = {
		0.0f,  15.0f,  0.0f,
		0.0f, 2000.0f, 0.0f
	};

	if (Window::GetInstance()->GetKey[F2])
	{
		Renderer::BeginLineStrip();

		glColor3f(1.0f, 0.0f, 0.0f);

		for (int i = 0; i < 6; i += 3)
		{
			glVertex3fv(&vertices[i]);
		}

		Renderer::End();
	}
}