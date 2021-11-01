#include "Ship.h"

#include "Engine/Window/Window.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/GLFunctions.h"
#include <Windows.h>

Ship::Ship(Vec2 position)
	:m_Position(position), m_Translate(Vec2(0.0f, 0.0f)), m_Angle(0.0f), m_Velocity{ 0.0f, 0.0f }, m_Accelaration{ 0.0f, 0.0f }, m_IsAccelarating(false)
{
	m_BodyVertices[0] = Vec3(  0.0f,  15.0f, 0.0f);
	m_BodyVertices[1] = Vec3( 10.0f, -10.0f, 0.0f);
	m_BodyVertices[2] = Vec3(  0.0f,   0.0f, 0.0f);
	m_BodyVertices[3] = Vec3(-10.0f, -10.0f, 0.0f);

	m_ThrusterVertices[0] = Vec3( 10.0f, -10.0f, 0.0f);
	m_ThrusterVertices[1] = Vec3( 15.0f, -15.0f, 0.0f);
	m_ThrusterVertices[2] = Vec3(  5.0f, -15.0f, 0.0f);
	m_ThrusterVertices[3] = Vec3(-10.0f, -10.0f, 0.0f);
	m_ThrusterVertices[4] = Vec3(-15.0f, -15.0f, 0.0f);
	m_ThrusterVertices[5] = Vec3( -5.0f, -15.0f, 0.0f);
}

Ship::~Ship()
{
}

void Ship::OnUpdate(float dt)
{
	if (Window::GetInstance()->GetKey[D])
	{
		m_Angle -= (5 * dt);
	}
	else if (Window::GetInstance()->GetKey[A])
	{
		m_Angle += (5 * dt);
	}

	if (Window::GetInstance()->GetKey[W])
	{
		m_IsAccelarating = true;
	}
	else
	{
		m_IsAccelarating = false;
	}

	Vec2 forwardDir = GetNosePosition().GetNormalised();

	if (m_IsAccelarating)
	{
		m_Accelaration = Vec2(2.5f * dt, 2.5f * dt);
	}
	else 
	{
		m_Accelaration = Vec2(0.0f, 0.0f);
	}

	m_Velocity += m_Accelaration * forwardDir * dt;

	m_Translate += m_Velocity * dt;

	Translation();

	Rotation();
}

void Ship::Render()
{

	float vertices[12] = {
		m_BodyVertices[0].m_X, m_BodyVertices[0].m_Y, m_BodyVertices[0].m_Z,
		m_BodyVertices[1].m_X, m_BodyVertices[1].m_Y, m_BodyVertices[1].m_Z,
		m_BodyVertices[2].m_X, m_BodyVertices[2].m_Y, m_BodyVertices[2].m_Z,
		m_BodyVertices[3].m_X, m_BodyVertices[3].m_Y, m_BodyVertices[3].m_Z
	};

	Renderer::BeginLineLoop();

	glColor3f(1.0f, 0.8f, 0.0f);
	
	for (int i = 0; i < 12; i += 3)
	{
		glVertex3fv(&vertices[i]);
	}

	Renderer::End();

	float vertices1[12] = {
		m_ThrusterVertices[0].m_X, m_ThrusterVertices[0].m_Y, m_ThrusterVertices[0].m_Z,
		m_ThrusterVertices[1].m_X, m_ThrusterVertices[1].m_Y, m_ThrusterVertices[1].m_Z,
		Random::GetRandomFloatInRange(7.5f, 12.5f), -27.5f, 0.0f,
		m_ThrusterVertices[2].m_X, m_ThrusterVertices[2].m_Y, m_ThrusterVertices[2].m_Z
	};
	
	float vertices2[12] = {
		m_ThrusterVertices[3].m_X, m_ThrusterVertices[3].m_Y, m_ThrusterVertices[3].m_Z,
		m_ThrusterVertices[4].m_X, m_ThrusterVertices[4].m_Y, m_ThrusterVertices[4].m_Z,
		Random::GetRandomFloatInRange(-12.5f, -7.5f), -27.5f, 0.0f,
		m_ThrusterVertices[5].m_X, m_ThrusterVertices[5].m_Y, m_ThrusterVertices[5].m_Z
	};
	
	if (Window::GetInstance()->GetKey[W])
	{
		Renderer::BeginQuads();
	
		glColor3f(1.0f, 0.27f, 0.0f);
	
		for (int i = 0; i < 12; i += 3)
		{
			glVertex3fv(&vertices1[i]);
		}
	
		Renderer::End();
	
		Renderer::BeginQuads();
	
		glColor3f(1.0f, 0.27f, 0.0f);
	
		for (int i = 0; i < 12; i += 3)
		{
			glVertex3fv(&vertices2[i]);
		}
	
		Renderer::End();
	}
}

void Ship::Translation()
{
	glLoadIdentity();

	if ((m_Position.m_X + m_Translate.m_X > 0.0f && m_Position.m_X + m_Translate.m_X < 1024.0f) 
		&& (m_Position.m_Y + m_Translate.m_Y > 0.0f && m_Position.m_Y + m_Translate.m_Y < 768.0f))
	{
		glTranslatef(m_Position.m_X + m_Translate.m_X, m_Position.m_Y + m_Translate.m_Y, 0.0f);
	}

	if (m_Position.m_X + m_Translate.m_X < 0.0f)
	{
		m_Translate.m_X = 1024.0f + (float)((int)(m_Translate.m_X) % 1024);
	}

	if (m_Position.m_Y + m_Translate.m_Y < 0.0f)
	{
		m_Translate.m_Y = 768.0f + (float)((int)(m_Translate.m_Y) % 768);
	}

	if (m_Position.m_X + m_Translate.m_X > 1024.0f)
	{
		m_Translate.m_X = (float)((int)(m_Position.m_X + m_Translate.m_X) % 1024) - m_Position.m_X;
	}

	if (m_Position.m_Y + m_Translate.m_Y > 768.0f)
	{
		m_Translate.m_Y = (float)((int)(m_Position.m_Y + m_Translate.m_Y) % 768) - m_Position.m_Y;
	}
}

void Ship::Rotation()
{
	glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
}

Vec2 Ship::GetNosePosition()
{
	Vec2 temp;
	temp.m_X = 15.0f * sinf(-m_Angle * ((float)M_PI / 180.0f));
	temp.m_Y = 15.0f * cosf(-m_Angle * ((float)M_PI / 180.0f));
	return temp;
}