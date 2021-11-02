#include "MeshBuilder.h"

#include "Mesh.h"

std::vector<VertexBufferElement> VertexMaster::PCU::m_Attributes = {
	VertexBufferElement(GL_FLOAT, 3, GL_FALSE),
	VertexBufferElement(GL_FLOAT, 4, GL_FALSE),
	VertexBufferElement(GL_FLOAT, 2, GL_FALSE)
};

VertexBufferLayout VertexMaster::PCU::m_Layout(PCU::m_Attributes, sizeof(PCU));

int VertexMaster::m_Size = 0;

VertexBufferLayout::VertexBufferLayout(const std::vector<VertexBufferElement> element, unsigned int stride)
	: m_Element(element), m_Stride(stride)
{
}

VertexBufferElement::VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized)
	: m_Type(type), m_ElementCount(count), m_Normalized(normalized)
{
}

VertexMaster::VertexMaster(Vec3 position, Vec4 color, Vec2 uv)
{
	PushUVCoords(uv);
	PushColorCoords(color);
	PushPosCoords(position);
}

VertexMaster::~VertexMaster()
{
}

void VertexMaster::PushPosCoords(Vec3 position)
{
	m_Pos = position;
	m_Size++;
}

void VertexMaster::PushColorCoords(Vec4 color)
{
	m_Color = color;
	m_Size++;
}

void VertexMaster::PushUVCoords(Vec2 uv)
{
	m_UV = uv;
	m_Size++;
}

MeshBuilder::MeshBuilder()
{
}

MeshBuilder::~MeshBuilder()
{
}

void MeshBuilder::Push(VertexMaster vertex)
{
	m_Vertices.push_back(vertex);
}

template <typename FORMAT>
Mesh* MeshBuilder::CreateMesh()
{
	size_t size = m_Vertices.size();

	Mesh* mesh = nullptr;

	std::cout << VertexMaster::m_Size;

	if (VertexMaster::m_Size / size == 3)
	{
		float* temp = new float[9 * size];

		for (int i = 0; i < size; i++)
		{ 
			temp[i * 9]       = m_Vertices[i].m_Pos.m_X;
			temp[(i * 9) + 1] = m_Vertices[i].m_Pos.m_Y;
			temp[(i * 9) + 2] = m_Vertices[i].m_Pos.m_Z;
			temp[(i * 9) + 3] = m_Vertices[i].m_Color.m_X;
			temp[(i * 9) + 4] = m_Vertices[i].m_Color.m_Y;
			temp[(i * 9) + 5] = m_Vertices[i].m_Color.m_Z;
			temp[(i * 9) + 6] = m_Vertices[i].m_Color.m_W;
			temp[(i * 9) + 7] = m_Vertices[i].m_UV.m_X;
			temp[(i * 9) + 8] = m_Vertices[i].m_UV.m_Y;
		}

		mesh = new Mesh(temp, &FORMAT::m_Layout);

		delete[] temp;
	}

	return mesh;
}