#include "SpriteDefinition.h"

#include "Engine/Core/tinyxmlH.h"

SpriteDefinition::SpriteDefinition(const XMLElement& element)
{
	m_SpriteCoords = ParseXMLAttrib(element, "spriteCoords", Vec2(-1, -1));

	m_SpriteDim = ParseXMLAttrib(element, "spriteDimensions", Vec2(-1, -1));

	m_Tiles = ParseXMLAttrib(element, "tiles", Vec2(-1, -1));

	m_Color = ParseXMLAttrib(element, "color", Vec4(-1, -1, -1, -1));
}

SpriteDefinition::~SpriteDefinition()
{
}

XMLElement* SpriteDefinition::InitializeDef(const String& path)
{
	XMLDocument* doc = new XMLDocument();
       doc->LoadFile(path.c_str());
	
	XMLElement* root = doc->FirstChildElement()->FirstChildElement();

	return root;
}