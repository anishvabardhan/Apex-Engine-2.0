#pragma once

#include <string>

#include "Engine/Graphics/GLFunctions.h"

enum TEXTURESLOT {
	SLOT0  = GL_TEXTURE0,
	SLOT1  = GL_TEXTURE1,
	SLOT2  = GL_TEXTURE2,
	SLOT3  = GL_TEXTURE3,
	SLOT4  = GL_TEXTURE4,
	SLOT5  = GL_TEXTURE5,
	SLOT6  = GL_TEXTURE6,
	SLOT7  = GL_TEXTURE7,
	SLOT8  = GL_TEXTURE8,
	SLOT9  = GL_TEXTURE9,
	SLOT10 = GL_TEXTURE10,
	SLOT11 = GL_TEXTURE11,
	SLOT12 = GL_TEXTURE12,
	SLOT13 = GL_TEXTURE13,
	SLOT14 = GL_TEXTURE14,
	SLOT15 = GL_TEXTURE15,
	SLOT16 = GL_TEXTURE16,
	SLOT17 = GL_TEXTURE17,
	SLOT18 = GL_TEXTURE18,
	SLOT19 = GL_TEXTURE19,
	SLOT20 = GL_TEXTURE20,
	SLOT21 = GL_TEXTURE21,
	SLOT22 = GL_TEXTURE22,
	SLOT23 = GL_TEXTURE23,
	SLOT24 = GL_TEXTURE24,
	SLOT25 = GL_TEXTURE25,
	SLOT26 = GL_TEXTURE26,
	SLOT27 = GL_TEXTURE27,
	SLOT28 = GL_TEXTURE28,
	SLOT29 = GL_TEXTURE29,
	SLOT30 = GL_TEXTURE30,
	SLOT31 = GL_TEXTURE31
};

class Texture
{
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_Channels;
public:
	explicit Texture(const std::string& path);
	~Texture();

	void Bind(TEXTURESLOT slot) const;
	void UnBind() const;

	inline unsigned int GetHandle() { return m_RendererID; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};