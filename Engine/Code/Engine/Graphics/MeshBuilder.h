#pragma once

#include "Engine/Core/CoreIncludes.h"
#include "Engine/Graphics/GLFunctions.h"

struct Mesh;

struct VertexBufferElement
{
	unsigned int m_Type;
	unsigned int m_ElementCount;
	unsigned char m_Normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:           return 4;
		case GL_UNSIGNED_INT:    return 4;
		case GL_UNSIGNED_BYTE:   return 1;
		}

		return 0;
	}

	VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized);
};

struct VertexBufferLayout
{
	std::vector<VertexBufferElement> m_Element;
	unsigned int m_Stride;

	VertexBufferLayout(const std::vector<VertexBufferElement> element, unsigned int stride);
};

struct VertexMaster
{
	Vec3 m_Pos;
	Vec4 m_Color;
	Vec2 m_UV;

	VertexMaster() {}
	VertexMaster(Vec3 position, Vec4 color, Vec2 uv) : m_Pos(position), m_Color(color), m_UV(uv) {}
	~VertexMaster();
};

struct VertexPCU
{
	Vec3 m_Pos;
	Vec4 m_Color;
	Vec2 m_UV;

	VertexPCU() {}
	VertexPCU(Vec3 position, Vec4 color, Vec2 uv);
	~VertexPCU();

	static std::vector<VertexBufferElement> m_Attributes;
	static VertexBufferLayout m_Layout;
};

struct MeshBuilder
{
	std::vector<VertexMaster> m_Vertices;

	MeshBuilder();
	~MeshBuilder();

	void Push(VertexMaster vertex);

	template<typename FORMAT>
	Mesh* CreateMesh();
};

template Mesh* MeshBuilder::CreateMesh<VertexPCU>();