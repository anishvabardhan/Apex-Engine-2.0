#pragma once

#include <string>
#include <map>

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

static std::map<int, TEXTURESLOT> m_TextureSlot = {
	{0 , SLOT0 },
	{1 , SLOT1 },
	{2 , SLOT2 },
	{3 , SLOT3 },
	{4 , SLOT4 },
	{5 , SLOT5 },
	{6 , SLOT6 },
	{7 , SLOT7 },
	{8 , SLOT8 },
	{9 , SLOT9 },
	{10, SLOT10},
	{11, SLOT11},
	{12, SLOT12},
	{13, SLOT13},
	{14, SLOT14},
	{15, SLOT15},
	{16, SLOT16},
	{17, SLOT17},
	{18, SLOT18},
	{19, SLOT19},
	{20, SLOT20},
	{21, SLOT21},
	{22, SLOT22},
	{23, SLOT23},
	{24, SLOT24},
	{25, SLOT25},
	{26, SLOT26},
	{27, SLOT27},
	{28, SLOT28},
	{29, SLOT29},
	{30, SLOT30},
	{31, SLOT31}
};

class Texture
{
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_Channels;
public:
	friend class Renderer;

	Texture();
	explicit Texture(const std::string& path);
	~Texture();

	void Bind(TEXTURESLOT slot) const;
	void UnBind() const;

	inline unsigned int GetHandle() { return m_RendererID; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};