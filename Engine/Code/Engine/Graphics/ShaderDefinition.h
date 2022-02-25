#pragma once

#include "Engine/Core/CoreIncludes.h"



class ShaderDefinition
{
public:
	String m_FilePath;
	String m_BlendOp;
	String m_BlendSRC;
	String m_BlendDST;

	ShaderDefinition(const XMLElement& element);
	~ShaderDefinition();

	static XMLElement* InitializeDef(const String& path);
};