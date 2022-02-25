#pragma once

#include "Engine/Core/CoreIncludes.h"
#include "SpriteSheet.h"
#include "Texture.h"

class Font
{
	SpriteSheet m_SpriteSheet;
public:
	explicit Font(const SpriteSheet& glyphSheet);
	~Font();

	AABB2 GetGlyphUV(int glyphAscii);
	float GetStringWidth(const String& asciiText, float cellHeight);
	const Texture* GetSpriteTexture() const;
	inline SpriteSheet GetSpriteSheet() const { return m_SpriteSheet; }
};