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
	FrameBuffer* m_SrcBuffer = nullptr;
	FrameBuffer* m_DestBuffer = nullptr;
public:
	Game();
	~Game();

	void BeginFrame();
	void Update(float deltaseconds);
	void Render();
	void EndFrame();
};