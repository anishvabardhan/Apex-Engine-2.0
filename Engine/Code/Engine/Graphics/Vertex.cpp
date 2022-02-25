#include "Vertex.h"

std::vector<VertexBufferElement> VertexPCU::m_Attributes = {
	VertexBufferElement(APEX_FLOAT, 3, false),
	VertexBufferElement(APEX_FLOAT, 4, false),
	VertexBufferElement(APEX_FLOAT, 2, false)
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

VertexMaster::VertexMaster(const VertexPCU& pcu)
	:m_Pos(pcu.m_Pos), m_Color(pcu.m_Color), m_UV(pcu.m_UV)
{
}

VertexMaster::VertexMaster(const Vec3& position, const Vec4& color, const Vec2& uv)
    : m_Pos(position), m_Color(color), m_UV(uv)
{
}
