#include "ShaderDefinition.h"

ShaderDefinition::ShaderDefinition(const tinyxml2::XMLElement& element)
	: m_FilePath("Invalid"), m_BlendSRC("Invalid"), m_BlendDST("Invalid"), m_BlendOp("Invalid")
{
	const tinyxml2::XMLElement* defElement = element.FirstChildElement("program");
	
	if (defElement)
	{
		if (defElement->FindAttribute("src"))
		{
			m_FilePath = ParseXMLAttrib(*defElement, "src", m_FilePath);
		}
	}

	defElement = element.FirstChildElement("blend");

	if (defElement)
	{
		const tinyxml2::XMLElement* blendElement = defElement->FirstChildElement("alpha");

		if (blendElement)
		{
			m_BlendSRC = ParseXMLAttrib(*blendElement, "src", m_BlendSRC);

			m_BlendDST = ParseXMLAttrib(*blendElement, "dst", m_BlendDST);

			m_BlendOp = ParseXMLAttrib(*blendElement, "op", m_BlendOp);
		}
	}
}

ShaderDefinition::~ShaderDefinition()
{
}

tinyxml2::XMLElement* ShaderDefinition::InitializeDef(const std::string& path)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile(path.c_str());

	tinyxml2::XMLElement* root = doc->FirstChildElement();

	return root;
}