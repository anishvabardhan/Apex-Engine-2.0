#include "Vertex.h"

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

VertexPCU::VertexPCU(const VertexMaster& master)
	: m_Pos(master.m_Pos), m_Color(master.m_Color), m_UV(master.m_UV)
{
}

VertexPCU::VertexPCU(const Vec3& position, const Vec4& color, const Vec2& uv)
	: m_Pos(position), m_Color(color), m_UV(uv)
{
}

VertexPCU::~VertexPCU()
{
}