#pragma once

#include "Engine/Graphics/GLFunctions.h"

struct VertexBufferLayout;
class VertexArrayObject;
class VertexBuffer;
class IndexBuffer;

struct Mesh
{
	int m_Indices = 6;
	VertexBuffer* m_VBO;
	VertexBufferLayout* m_Layout;
	const void* m_Data;
	GLenum m_DrawType;
	VertexArrayObject* m_VAO;
	IndexBuffer* m_IBO;

	Mesh(const void* data, VertexBufferLayout* layout);
	~Mesh();

	void CopyToGPU();
	void Begin(GLenum drawType);
	void End();
};