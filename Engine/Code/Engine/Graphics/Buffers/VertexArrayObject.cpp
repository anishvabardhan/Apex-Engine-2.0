#include "VertexArrayObject.h"

#include "Engine/Graphics/MeshBuilder.h"
#include "Engine/Graphics/GLFunctions.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArrayObject::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.m_Element;
    int64_t offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.m_ElementCount, element.m_Type, element.m_Normalized, layout.m_Stride, (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += element.m_ElementCount * VertexBufferElement::GetSizeOfType(element.m_Type);
	}
}

void VertexArrayObject::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArrayObject::UnBind() const
{
	glBindVertexArray(0);
}