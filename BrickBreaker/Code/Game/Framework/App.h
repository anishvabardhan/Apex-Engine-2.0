#pragma once

class Game;
class Time;

class App
{
	Time* m_Time = nullptr;
	bool m_IsQuitting = false;
	bool m_IsSlowMo = false;
	bool m_IsPaused = false;
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