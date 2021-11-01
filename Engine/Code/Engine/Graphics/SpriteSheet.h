#pragma once


#include "Engine/Core/CoreIncludes.h"

#include "Texture.h"

class SpriteDefinition;

class SpriteSheet
{
public:
	Texture& m_SpriteSheetTexture;
	Vec2 m_Position;
	Vec2 m_Dimension;
	Vec2 m_SpriteLayout;
	Vec4 m_Color;

	SpriteSheet(Texture& texture, int tilesWide, int tilesHigh);
	SpriteSheet(Texture& texture, SpriteDefinition* def);
	~SpriteSheet();

	AABB2 GetTexCoords(int charAscii);
	Texture& GetSpriteSheetTexture() const { return m_SpriteSheetTexture; }
	const Vec2 GetLayout() const { return m_SpriteLayout; }
};