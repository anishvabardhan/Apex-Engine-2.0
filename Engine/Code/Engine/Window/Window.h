#pragma once

#include <Windows.h>
#include <iostream>

#include "Engine/Input/Input.h"

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
	
	BOOL MakeContextCurrent(HDC hdc, HGLRC hglrc);
	HGLRC CreateOldRenderContext(HDC hdc);
	HGLRC CreateRealRenderContext(HDC hdc, int major, int minor);

	virtual void OnCreate(HWND hwnd);
	virtual void OnUpdate();
	virtual void OnDestroy(HGLRC rendercontext);

	inline HDC GetDeviceContext() const { return m_OurWindowHandleToDeviceContext; }
	inline HGLRC GetRenderContext() const { return m_OurWindowHandleToRenderContext; }

	static Window* GetInstance();
protected:
	HWND m_Hwnd;
	HDC m_OurWindowHandleToDeviceContext;
	HGLRC m_OurWindowHandleToRenderContext;

	bool m_IsRun;
public:
	bool GetKey[256];
	bool GetMouse[256];
};