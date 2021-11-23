#pragma once

class Game;

class App
{
	bool m_IsQuitting = false;
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