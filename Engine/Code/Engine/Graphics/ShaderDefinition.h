#pragma once

#include "Engine/Core/CoreIncludes.h"



class ShaderDefinition
{
public:
	std::string m_FilePath;
	std::string m_BlendOp;
	std::string m_BlendSRC;
	std::string m_BlendDST;

	ShaderDefinition(const XMLElement& element);
	~ShaderDefinition();

	static XMLElement* InitializeDef(const std::string& path);
};