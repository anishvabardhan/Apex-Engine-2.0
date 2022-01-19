#pragma once

#include "KeyButtonState.h"
#include "Mouse.h"

constexpr int MAX_KEYS = 256;

class InputSystem
{
	KeyButtonState m_KeyState[MAX_KEYS];
	Mouse m_Mouse;
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
	Vec2 GetMousePosition();
	void SetMousePosition(const Vec2& clientPosition);

	bool HandleKeyUp(unsigned char KeyCode);
	bool HandleKeyDown(unsigned char KeyCode);
};