 #include "Texture.h"

#include "External/stb_image.h"

Texture::Texture()
	: m_RendererID(NULL), m_FilePath(""), m_Width(0), m_Height(0), m_LocalBuffer(nullptr)
{
}

Texture::Texture(const String& path)
	: m_RendererID(NULL), m_FilePath(path), m_Width(0), m_Height(0), m_LocalBuffer(nullptr)
{
	
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(TEXTURESLOT slot) const
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}