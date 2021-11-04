#include "InputSystem.h"

#include "Engine/Core/CoreMACROS.h"

InputSystem* g_InputSystem = nullptr;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::Startup()
{
}

void InputSystem::BeginFrame()
{
	
}

void InputSystem::Update(float deltaseconds)
{
	UNUSED(deltaseconds)
}

void InputSystem::Render()
{
}

void InputSystem::EndFrame()
{
	for(int keycode = 0; keycode < MAX_KEYS; keycode++)
	{
		m_KeyState[keycode].m_WasPressedLastFrame = m_KeyState[keycode].m_IsPressed;
	}
}

void InputSystem::ShutDown()
{
}

bool InputSystem::IsHeldDown(unsigned char KeyCode) const
{
	return m_KeyState[KeyCode].m_WasPressedLastFrame == true && m_KeyState[KeyCode].m_IsPressed == true;
}

bool InputSystem::WasKeyJustPressed(unsigned char KeyCode) const
{
	return m_KeyState[KeyCode].WasJustPressed();
}

bool InputSystem::WasKeyJustReleased(unsigned char KeyCode) const
{
	return m_KeyState[KeyCode].WasJustReleased();
}

bool InputSystem::HandleKeyUp(unsigned char KeyCode)
{
	m_KeyState[KeyCode].m_IsPressed = false;

	return m_KeyState[KeyCode].m_IsPressed;
}

bool InputSystem::HandleKeyDown(unsigned char KeyCode)
{
	m_KeyState[KeyCode].m_IsPressed = true;

	return m_KeyState[KeyCode].m_IsPressed;
}
