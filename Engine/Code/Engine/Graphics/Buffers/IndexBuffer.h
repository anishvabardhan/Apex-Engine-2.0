#pragma once

class IndexBuffer
{
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	explicit IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_Count; }
};