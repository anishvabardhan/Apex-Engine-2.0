#pragma once

#include "Engine/Graphics/GLFunctions.h"

#include "Engine/Core/CoreIncludes.h"

class ShaderDefinition;

struct ShaderProgramSource
{
	String VertexSource;
	String FragmentSource;
};

class Shader
{
	//----------------------------------------------------------------------------------------------
	// Member Variables

	String m_FilePath;
	String m_BlendOp;
	String m_BlendSRC;
	String m_BlendDST;
	unsigned int m_RendererID;
	std::unordered_map<String, int> m_UniformLocationCache;
public:
	explicit Shader(ShaderDefinition* shaderDef);
	explicit Shader(const String& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	inline String GetSRC() const { return m_BlendSRC; }
	inline String GetDST() const { return m_BlendDST; }
	inline String GetOP() const { return m_BlendOp; }

	//----------------------------------------------------------------------------------------------
	// Set Uniforms

	void SetUniform1i(const String& name, int value);
	void SetUniform4f(const String& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const String& name, const Mat4& matrix);
private:
	ShaderProgramSource ParseShader(const String& filepath);
	unsigned int CompileShader(unsigned int type, const String& source);
	unsigned int CreateShader(const String& vertexShader, const String& fragmentShader);

	int GetUniformLocation(const String& name);
};