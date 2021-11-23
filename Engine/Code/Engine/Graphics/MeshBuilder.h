#pragma once

#include "Engine/Core/CoreIncludes.h"

struct Mesh;
struct VertexBufferElement;
struct VertexBufferLayout;
struct VertexMaster;
struct VertexPCU;

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