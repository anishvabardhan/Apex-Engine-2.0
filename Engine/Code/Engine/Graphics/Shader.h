#pragma once

#include "Engine/Graphics/GLFunctions.h"

#include "Engine/Core/CoreIncludes.h"

class ShaderDefinition;

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
	//----------------------------------------------------------------------------------------------
	// Member Variables

	std::string m_FilePath;
	std::string m_BlendOp;
	std::string m_BlendSRC;
	std::string m_BlendDST;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	explicit Shader(ShaderDefinition* shaderDef);
	explicit Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	inline std::string GetSRC() const { return m_BlendSRC; }
	inline std::string GetDST() const { return m_BlendDST; }
	inline std::string GetOP() const { return m_BlendOp; }

	//----------------------------------------------------------------------------------------------
	// Set Uniforms

	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const Mat4& matrix);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);
};