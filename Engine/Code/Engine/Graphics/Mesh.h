#pragma once

#include "Engine/Graphics/GLFunctions.h"

struct VertexBufferLayout;
class VertexArrayObject;
class VertexBuffer;
class IndexBuffer;

struct Mesh
{
	int m_Indices = 6;
	VertexBuffer* m_VBO = nullptr;
	VertexBufferLayout* m_Layout = nullptr;
	const void* m_Data = nullptr;
	GLenum m_DrawType;
	VertexArrayObject* m_VAO = nullptr;
	IndexBuffer* m_IBO = nullptr;

	Mesh(const void* data, VertexBufferLayout* layout);
	~Mesh();

	void CopyToGPU();
	void Begin(GLenum drawType);
	void End();
};