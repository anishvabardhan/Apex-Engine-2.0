#pragma once

class Texture;

class FrameBuffer
{
	unsigned int m_FrameBufferID;
	unsigned int m_ColorAttachment;
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind();
	void UnBind();

	void Initialize();

	unsigned int GetFrameBufferID() const;
	unsigned int GetColorAttachmentID() const;
};