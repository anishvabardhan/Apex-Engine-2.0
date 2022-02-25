#pragma once

#include "Engine/Core/CoreIncludes.h"
#include "Engine/Core/XMLParser.h"

class SpriteDefinition
{
public:
	Vec2 m_SpriteCoords;
	Vec2 m_SpriteDim;
	Vec2 m_Tiles;
	Vec4 m_Color;

	SpriteDefinition(const XMLElement& element);
	~SpriteDefinition();

	static XMLElement* InitializeDef(const String& path);
};