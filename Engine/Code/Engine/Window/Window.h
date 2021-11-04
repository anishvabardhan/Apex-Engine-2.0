#pragma once

extern void* g_GLLibrary;

class Window
{
public:
	Window();
	~Window();

	bool Init();
	bool Broadcast();
	bool Release();
	bool IsRun();

	void SwappingBuffers();
	
	bool MakeContextCurrent(void* hdc, void* hglrc);
	void* CreateOldRenderContext(void* hdc);
	void* CreateRealRenderContext(void* hdc, int major, int minor);

	virtual void OnCreate(void* hwnd);
	virtual void OnUpdate();
	virtual void OnDestroy(void* rendercontext);

	inline void* GetDeviceContext() const { return m_OurWindowHandleToDeviceContext; }
	inline void* GetRenderContext() const { return m_OurWindowHandleToRenderContext; }

	static Window* GetInstance();
protected:
	void* m_Hwnd;
	void* m_OurWindowHandleToDeviceContext;
	void* m_OurWindowHandleToRenderContext;

	bool m_IsRun;
public:
	bool GetKey[256];
	bool GetMouse[256];
};