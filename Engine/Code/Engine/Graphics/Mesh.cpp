#include "Mesh.h"

#include "Buffers/VertexArrayObject.h"
#include "Buffers/IndexBuffer.h"
#include "MeshBuilder.h"

Mesh::Mesh(const void* data, VertexBufferLayout* layout)
	: m_VBO(nullptr), m_Layout(layout), m_Data(data)
{
	CopyToGPU();
}

Mesh::~Mesh()
{
	delete m_VAO;
	delete m_IBO;
	delete m_VBO;
}

void Mesh::CopyToGPU()
{
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_VAO = new VertexArrayObject();

	m_VBO = new VertexBuffer(m_Data, sizeof(m_Data) * m_Layout->m_Stride);

	m_VAO->AddBuffer(*m_VBO, *m_Layout);

	m_IBO = new IndexBuffer(indices, sizeof(indices));
}

void Mesh::Begin(GLenum drawType)
{
	m_DrawType = drawType;

	m_VAO->Bind();
	m_IBO->Bind();
}

void Mesh::End()
{
	m_IBO->Bind();
	m_VAO->Bind();
}