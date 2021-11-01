#pragma once

#include "VertexBuffer.h"
#include <vector>

struct VertexBufferLayout;

class VertexArrayObject
{
// Member Variables-------------------------------------------------------------------------------------

	unsigned int m_RendererID;
public:
	VertexArrayObject();
	~VertexArrayObject();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};