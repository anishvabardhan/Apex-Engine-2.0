#include "Shader.h"

#include "ShaderDefinition.h"
#include "Engine/Core/CoreIncludes.h"
#include "Renderer.h"

extern Renderer* g_Renderer;

Shader::Shader(ShaderDefinition* shaderDef)
	: m_RendererID(0)
{
	m_FilePath = shaderDef->m_FilePath;
	m_BlendSRC = shaderDef->m_BlendSRC;
	m_BlendDST = shaderDef->m_BlendDST;
	m_BlendOp = shaderDef->m_BlendOp;

	ShaderProgramSource source = ParseShader(m_FilePath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::Shader(const String& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(m_FilePath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ParseShader(const String& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	String line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != String::npos)
		{
			if (line.find("vertex") != String::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != String::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const String& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return id;
}

unsigned int Shader::CreateShader(const String& vertexShader, const String& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);

	g_Renderer->BindTexture();
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const String& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const String& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const String& name, const Mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.elements);
}

int Shader::GetUniformLocation(const String& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: Uniform '" << name << "' doesn't exist!" << std::endl;
	
	m_UniformLocationCache[name] = location;
	return location;
}