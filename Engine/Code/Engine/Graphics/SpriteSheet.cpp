#include "SpriteSheet.h"

#include "Engine/Graphics/SpriteDefinition.h"

SpriteSheet::SpriteSheet(Texture& texture, int tilesWide, int tilesHigh)
	: m_SpriteSheetTexture(texture), m_SpriteLayout(Vec2((float)tilesWide, (float)tilesHigh))
{
}

SpriteSheet::SpriteSheet(Texture& texture, SpriteDefinition* def)
	: m_SpriteSheetTexture(texture)
{
	m_Position = def->m_SpriteCoords;
	m_Dimension = def->m_SpriteDim;
	m_SpriteLayout = def->m_Tiles;
	m_Color = def->m_Color;
}

SpriteSheet::~SpriteSheet()
{
}

AABB2 SpriteSheet::GetTexCoords(int charAscii)
{
	Vec2 spriteCoords;
	AABB2 texCoords;

	spriteCoords.m_X = float(charAscii % (int)m_SpriteLayout.m_Y);
	spriteCoords.m_Y = m_SpriteLayout.m_Y - (int(charAscii / (int)m_SpriteLayout.m_Y));

	texCoords.m_Mins.m_X = spriteCoords.m_X / m_SpriteLayout.m_X;
	texCoords.m_Mins.m_Y = spriteCoords.m_Y / m_SpriteLayout.m_Y;

	texCoords.m_Maxs.m_X = (spriteCoords.m_X + 1) / m_SpriteLayout.m_X;
	texCoords.m_Maxs.m_Y = (spriteCoords.m_Y - 1) / m_SpriteLayout.m_Y;

	return texCoords;
}