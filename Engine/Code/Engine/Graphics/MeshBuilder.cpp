#include "MeshBuilder.h"

#include "Mesh.h"
#include "Vertex.h"

MeshBuilder::MeshBuilder()
{
}

MeshBuilder::~MeshBuilder()
{
}

void MeshBuilder::Color3f(Vec4 color)
{
	m_Color = color;
}

void MeshBuilder::TexCoord2f(Vec2 uv)
{
	m_VertMast.m_UV = uv;
}

// TODO No Resets, 

void MeshBuilder::ResetLocalVertex()
{
	memset(&m_VertMast, 0, sizeof(m_VertMast));
}

void MeshBuilder::Position3f(Vec3 position)
{
	m_VertMast.m_Color = m_Color;
	m_VertMast.m_Pos = position;
	
	m_Vertices.push_back(m_VertMast);

	ResetLocalVertex();
}

void MeshBuilder::Vert(const VertexMaster& master)
{
	m_Vertices.emplace_back(master);
}

template <typename FORMAT>
Mesh* MeshBuilder::CreateMesh()
{
	size_t size = m_Vertices.size();
	FORMAT* temp = new FORMAT[sizeof(FORMAT) * size]; 

	Mesh* mesh = nullptr;

	for(size_t index = 0; index < size; index++)
	{
		temp[index] = FORMAT(m_Vertices[index]);
	}

	mesh = new Mesh(temp, &FORMAT::m_Layout);
	
	delete[] temp;
	temp = nullptr;

	return mesh;
}