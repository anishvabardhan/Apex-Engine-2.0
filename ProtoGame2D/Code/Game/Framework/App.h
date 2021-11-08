#pragma once

class Game;
class ShaderDefinition;
class Shader;
class FrameBuffer;

class App
{
	bool m_IsQuitting = false;

	ShaderDefinition* m_ShaderDef = nullptr;
	ShaderDefinition* m_ScreenShaderDef = nullptr;
	Shader* m_Shader = nullptr;
	Shader* m_ScreenShader = nullptr;
	FrameBuffer* m_CurrentBuffer = nullptr;
	FrameBuffer* m_NextBuffer = nullptr;
public:
	Game* m_Game = nullptr;
public:
	App();
	~App();

	void Startup();
	void RunFrame();
	 void BeginFrame();
	 void Update(float deltaseconds);
	 void Render();
	 void EndFrame();
	void Shutdown();

	bool IsAppQuitting() const { return m_IsQuitting; }
private:
	void UpdateFromInput();
};