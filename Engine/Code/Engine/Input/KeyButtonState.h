#pragma once

class KeyButtonState
{
	bool m_IsPressed = false;
	bool m_WasPressedLastFrame = false;
public:
	bool IsPressed() const { return m_IsPressed; }
	bool WasJustPressed() const;
	bool WasJustReleased() const;
	void Reset();
	void UpdateButtonState(bool isNowPressed);
private:
	friend class InputSystem;
};