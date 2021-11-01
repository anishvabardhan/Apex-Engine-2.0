#pragma once

class Game
{
public:
	Game();
	~Game();

	void BeginFrame();
	void Update();
	void Render();
	void EndFrame();
};

