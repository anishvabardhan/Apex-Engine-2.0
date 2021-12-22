#pragma once
#include <string>

class InputSystem;

class Window
{
	InputSystem* m_InputSystem = nullptr;
public:
	Window();
	~Window();

	void Init(const std::string& appName, const long clientDims[4]);
	bool RunMessagePump();
	bool Destroy();

	void OnUpdate();

	inline void AppQuitting() { m_IsQuitting = true; }
	bool IsAppQuiting();

	inline void* GetHandle() const { return m_Hwnd; }
	inline void* GetDeviceContext() const { return m_OurWindowHandleToDeviceContext; }
	inline void* GetRenderContext() const { return m_OurWindowHandleToRenderContext; }

	inline InputSystem* GetInputSystem() const { return m_InputSystem; }
	inline void SetInputSystem(InputSystem* inputSystem) { m_InputSystem = inputSystem; }

	void SetTitle(const std::wstring& title);

	static Window* GetInstance();
protected:
	void* m_Hwnd = nullptr;
	void* m_OurWindowHandleToDeviceContext = nullptr;
	void* m_OurWindowHandleToRenderContext = nullptr;

	bool m_IsQuitting = false;
public:
	bool GetMouse[256];
};