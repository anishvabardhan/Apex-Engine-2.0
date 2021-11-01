#include "SpriteDefinition.h"

SpriteDefinition::SpriteDefinition(const tinyxml2::XMLElement& element)
{
	m_SpriteCoords = ParseXMLAttrib(element, "spriteCoords", Vec2(-1, -1));

	m_SpriteDim = ParseXMLAttrib(element, "spriteDimensions", Vec2(-1, -1));

	m_Tiles = ParseXMLAttrib(element, "tiles", Vec2(-1, -1));

	m_Color = ParseXMLAttrib(element, "color", Vec4(-1, -1, -1, -1));
}

SpriteDefinition::~SpriteDefinition()
{
}

tinyxml2::XMLElement* SpriteDefinition::InitializeDef(const std::string& path)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
       doc->LoadFile(path.c_str());
	
	tinyxml2::XMLElement* root = doc->FirstChildElement()->FirstChildElement();

	return root;
}