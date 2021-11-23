#include "MeshBuilder.h"

#include "Mesh.h"
#include "Vertex.h"

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