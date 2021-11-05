#pragma once
#include <string>

extern void* g_GLLibrary;

class InputSystem;

class Window
{
	InputSystem* m_InputSystem = nullptr;
public:
	Window();
	~Window();

	void Init(const std::string& appName);
	bool Broadcast();
	bool Release();

	void SwappingBuffers();
	
	bool MakeContextCurrent(void* hdc, void* hglrc);
	void* CreateOldRenderContext(void* hdc);
	void* CreateRealRenderContext(void* hdc, int major, int minor);

	virtual void OnCreate(void* hwnd);
	virtual void OnUpdate();
	virtual void OnDestroy(void* rendercontext);

	inline void AppQuitting() { m_IsQuitting = true; }
	bool IsAppQuiting();

	inline void* GetDeviceContext() const { return m_OurWindowHandleToDeviceContext; }
	inline void* GetRenderContext() const { return m_OurWindowHandleToRenderContext; }

	inline InputSystem* GetInputSystem() const { return m_InputSystem; }
	inline void SetInputSystem(InputSystem* inputSystem) { m_InputSystem = inputSystem; }

	void SetTitle(const std::wstring& title);

	static Window* GetInstance();
protected:
	void* m_Hwnd;
	void* m_OurWindowHandleToDeviceContext;
	void* m_OurWindowHandleToRenderContext;

	bool m_IsQuitting = false;
public:
	bool GetMouse[256];
};