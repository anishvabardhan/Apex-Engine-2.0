#pragma once

class Shader;

class Paddle
{
public:
	Paddle();
	~Paddle();

	void Update(float deltaseconds);
	void Render(Shader shader);
};