#pragma once

#include "Engine/Core/CoreIncludes.h"

struct Mesh;
struct VertexBufferElement;
struct VertexBufferLayout;
struct VertexMaster;
struct VertexPCU;

struct MeshBuilder
{
	VertexMaster* m_VertMast = nullptr;
	std::vector<VertexMaster> m_Vertices;

	MeshBuilder();
	~MeshBuilder();

	void Color3f(Vec4 color);
	void TexCoord2f(Vec2 uv);
	void Position3f(Vec3 position);
	void Push();

	template<typename FORMAT>
	Mesh* CreateMesh();
};

template Mesh* MeshBuilder::CreateMesh<VertexPCU>();