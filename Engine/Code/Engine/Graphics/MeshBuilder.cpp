#include "MeshBuilder.h"

#include "Mesh.h"

std::vector<VertexBufferElement> VertexPCU::m_Attributes = {
	VertexBufferElement(GL_FLOAT, 3, GL_FALSE),
	VertexBufferElement(GL_FLOAT, 4, GL_FALSE),
	VertexBufferElement(GL_FLOAT, 2, GL_FALSE)
};

VertexBufferLayout VertexPCU::m_Layout(VertexPCU::m_Attributes, sizeof(VertexPCU));

VertexBufferLayout::VertexBufferLayout(const std::vector<VertexBufferElement> element, unsigned int stride)
	: m_Element(element), m_Stride(stride)
{
}

VertexBufferElement::VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized)
	: m_Type(type), m_ElementCount(count), m_Normalized(normalized)
{
}

VertexPCU::VertexPCU(VertexMaster master)
	: m_Pos(master.m_Pos), m_Color(master.m_Color), m_UV(master.m_UV)
{
}

VertexPCU::VertexPCU(Vec3 position, Vec4 color, Vec2 uv)
	: m_Pos(position), m_Color(color), m_UV(uv)
{
}

VertexPCU::~VertexPCU()
{
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
	FORMAT* temp = new FORMAT[sizeof(FORMAT) * size]; 

	Mesh* mesh = nullptr;

	for(size_t index = 0; index < size; index++)
	{
		temp[index] = FORMAT(m_Vertices[index]);
	}

	mesh = new Mesh(temp, &FORMAT::m_Layout);
	
	delete[] temp;

	return mesh;
}