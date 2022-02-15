#pragma once
#include "Engine/Maths/Vec2.h"

class Texture;

class FrameBuffer
{
	unsigned int m_FrameBufferID;
	unsigned int m_ColorAttachment;
public:
		Vec2 m_Dims;
public:
	FrameBuffer(const Vec2 dimensions);
	~FrameBuffer();

	void Bind();
	void UnBind();

	void Initialize();

	unsigned int GetFrameBufferID() const;
	unsigned int GetColorAttachmentID() const;
};