#pragma once

#include "Engine/Core/CoreIncludes.h"
#include "Vertex.h"

struct Mesh;

struct MeshBuilder
{
	Vec4 m_Color;
	VertexMaster m_VertMast;
	std::vector<VertexMaster> m_Vertices;

	MeshBuilder();
	~MeshBuilder();

	void Color3f(Vec4 color);
	void TexCoord2f(Vec2 uv);
	void Position3f(Vec3 position);
	void Vert(const VertexMaster& master);
	void ResetLocalVertex();

	template<typename FORMAT>
	Mesh* CreateMesh();
};

template Mesh* MeshBuilder::CreateMesh<VertexPCU>();