#pragma once

class ShaderDefinition;
class Shader;
class FrameBuffer;

class Game
{
	ShaderDefinition* m_ShaderDef = nullptr;
	ShaderDefinition* m_ScreenShaderDef = nullptr;
	Shader* m_Shader = nullptr;
	Shader* m_ScreenShader = nullptr;
	FrameBuffer* m_CurrentBuffer = nullptr;
	FrameBuffer* m_NextBuffer = nullptr;
public:
	Game();
	~Game();

	void BeginFrame();
	void Update();
	void Render();
	void EndFrame();
};