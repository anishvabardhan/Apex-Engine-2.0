#pragma once

#include "KeyButtonState.h"

constexpr int MAX_KEYS = 256;

class InputSystem
{
	KeyButtonState m_KeyState[MAX_KEYS];
public:
	InputSystem();
	~InputSystem();

	void Startup();
	void BeginFrame();
	void Update(float deltaseconds);
	void Render();
	void EndFrame();
	void ShutDown();

	bool IsHeldDown(unsigned char KeyCode) const;
	bool WasKeyJustPressed(unsigned char KeyCode) const;
	bool WasKeyJustReleased(unsigned char KeyCode) const;

	bool HandleKeyUp(unsigned char KeyCode);
	bool HandleKeyDown(unsigned char KeyCode);
};