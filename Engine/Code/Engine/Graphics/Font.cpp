#include "Font.h"

Font::Font(SpriteSheet glyphSheet)
	: m_SpriteSheet(glyphSheet)
{
}

Font::~Font()
{
}

AABB2 Font::GetGlyphUV(int glyphAscii)
{
	AABB2 uv = m_SpriteSheet.GetTexCoords(glyphAscii);

	return uv;
}

float Font::GetStringWidth(const std::string& asciiText, float cellHeight)
{
	float cellWidth = cellHeight;

	return cellWidth * asciiText.length();
}

const Texture* Font::GetSpriteTexture() const
{
	return &m_SpriteSheet.GetSpriteSheetTexture();
}