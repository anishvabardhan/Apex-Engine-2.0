#include "ShaderDefinition.h"

#include "Engine/Core/XMLParser.h"
#include "Engine/Core/tinyxmlH.h"

ShaderDefinition::ShaderDefinition(const XMLElement& element)
	: m_FilePath("Invalid"), m_BlendSRC("Invalid"), m_BlendDST("Invalid"), m_BlendOp("Invalid")
{
	const XMLElement* defElement = element.FirstChildElement("program");
	
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
		const XMLElement* blendElement = defElement->FirstChildElement("alpha");

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

XMLElement* ShaderDefinition::InitializeDef(const std::string& path)
{
	XMLDocument* doc = new XMLDocument();
	doc->LoadFile(path.c_str());

	XMLElement* root = doc->FirstChildElement();

	return root;
}