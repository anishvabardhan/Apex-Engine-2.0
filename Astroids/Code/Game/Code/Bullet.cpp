#include "Bullet.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphics/GLFunctions.h"
#include "Ship.h"

Bullet::Bullet(const Vec2& position)
	:m_Position(position), m_Radius(2.0f), m_NumOfVertices(10), m_Age(0.0f)
{
	GLfloat twicePi = 2.0f * (GLfloat)M_PI;

	for (int i = 0; i < m_NumOfVertices; i++)
	{
		m_BodyVertices[i] = Vec3((m_Radius * cos(i * twicePi / m_NumOfVertices)), (m_Radius * sin(i * twicePi / m_NumOfVertices)), 0.0f);
	}
}

Bullet::~Bullet()
{
}

void Bullet::OnUpdate(Vec2 update, float dt)
{
	update += m_Position;

	m_Age += dt;

	if ((update.m_X > 0.0f && update.m_X < 1024.0f)
		&& (update.m_Y > 0.0f && update.m_Y < 768.0f))
	{
		glTranslatef(update.m_X, update.m_Y, 0.0f);
	}
}

void Bullet::Render()
{
	GLfloat vertices[30] = {
		m_BodyVertices[0].m_X, m_BodyVertices[0].m_Y, m_BodyVertices[0].m_Z,
		m_BodyVertices[1].m_X, m_BodyVertices[1].m_Y, m_BodyVertices[1].m_Z,
		m_BodyVertices[2].m_X, m_BodyVertices[2].m_Y, m_BodyVertices[2].m_Z,
		m_BodyVertices[3].m_X, m_BodyVertices[3].m_Y, m_BodyVertices[3].m_Z,
		m_BodyVertices[4].m_X, m_BodyVertices[4].m_Y, m_BodyVertices[4].m_Z,
		m_BodyVertices[5].m_X, m_BodyVertices[5].m_Y, m_BodyVertices[5].m_Z,
		m_BodyVertices[6].m_X, m_BodyVertices[6].m_Y, m_BodyVertices[6].m_Z,
		m_BodyVertices[7].m_X, m_BodyVertices[7].m_Y, m_BodyVertices[7].m_Z,
		m_BodyVertices[8].m_X, m_BodyVertices[8].m_Y, m_BodyVertices[8].m_Z,
		m_BodyVertices[9].m_X, m_BodyVertices[9].m_Y, m_BodyVertices[9].m_Z
	};

	Renderer::BeginPolygon();

	glColor3f(0.0f, 1.0f, 0.0f);

	for (int i = 0; i < m_NumOfVertices * 3; i += 3)
	{
		glVertex3fv(&vertices[i]);
	}

	Renderer::End();
}