#pragma once

#include "VertexBuffer.h"
#include <vector>

struct VertexBufferLayout;

class VertexArrayObject
{
	unsigned int m_RendererID;
public:
	VertexArrayObject();
	~VertexArrayObject();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};