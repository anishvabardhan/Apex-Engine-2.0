#include "Mesh.h"

#include "Buffers/VertexArrayObject.h"
#include "Buffers/IndexBuffer.h"
#include "MeshBuilder.h"
#include "Vertex.h"

Mesh::Mesh(const void* data, VertexBufferLayout* layout)
	: m_VBO(nullptr), m_Layout(layout), m_Data(data)
{
	CopyToGPU();
}

Mesh::~Mesh()
{
	delete m_VBO;
	delete m_VAO;

	if(m_IBO)
	{
		delete m_IBO;
	}
}

void Mesh::CopyToGPU()
{
	m_VAO = new VertexArrayObject();

	m_VBO = new VertexBuffer(m_Data, sizeof(m_Data) * m_Layout->m_Stride);

	m_VAO->AddBuffer(*m_VBO, *m_Layout);

	if(m_Indices == 6)
	{
		unsigned int indices[] = {
		    0, 1, 2,
		    2, 3, 0
	    };

	    m_IBO = new IndexBuffer(indices, sizeof(indices));
	}
}

void Mesh::Begin(GLenum drawType)
{
	m_DrawType = drawType;

	m_VAO->Bind();
	if(m_Indices == 6)
	{
		m_IBO->Bind();
	}
}

void Mesh::End()
{
	if(m_Indices == 6)
	{
		m_IBO->UnBind();
	}
	m_VAO->UnBind();
}