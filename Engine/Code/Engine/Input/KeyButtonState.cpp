#include "KeyButtonState.h"

bool KeyButtonState::WasJustPressed() const
{
	return m_WasPressedLastFrame == false && m_IsPressed == true;
}

bool KeyButtonState::WasJustReleased() const
{
	if(m_WasPressedLastFrame == true && m_IsPressed == false)
	{
		return m_WasPressedLastFrame;
	}

	return false;
}

void KeyButtonState::Reset()
{
	m_IsPressed = false;
	m_WasPressedLastFrame = false;
}

void KeyButtonState::UpdateButtonState(bool isNowPressed)
{
	m_WasPressedLastFrame = m_IsPressed;
	m_IsPressed = isNowPressed;
}
