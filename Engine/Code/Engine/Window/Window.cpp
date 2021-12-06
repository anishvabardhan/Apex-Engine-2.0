#include "Window.h"

#include "Engine/Platform/WindowsH.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Core/CoreMACROS.h"

Window* g_Window = nullptr;

extern InputSystem* g_InputSystem;

Window::Window()
	: m_Hwnd(NULL), m_OurWindowHandleToDeviceContext(NULL), m_OurWindowHandleToRenderContext(NULL)
{
}

Window::~Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	Window* myWindow = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);


	InputSystem* input = nullptr;

	if(myWindow)
	{
		input = myWindow->GetInputSystem();
	}
	else
	{
		printf("\nWINDOWS NOT FOUND!!\n");
	}

	switch (msg)
	{
	case WM_CREATE:
	{
		myWindow = (Window*)lparam;
		::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)myWindow);
		break;
	}
	case WM_CLOSE:
	{
		g_Window->AppQuitting();
		::PostQuitMessage(0);
			return NULL;
	}
	case WM_KEYDOWN:
	{
		unsigned char keycode = (unsigned char)wparam;
		input->HandleKeyDown(keycode);
		break;
	}

	case WM_KEYUP:
	{
		unsigned char keycode = (unsigned char)wparam;
		input->HandleKeyUp(keycode);
		break;
	}

	case WM_LBUTTONDOWN:
	{
		g_Window->GetMouse[wparam] = true;
		break;
	}

	case WM_LBUTTONUP:
	{
		g_Window->GetMouse[wparam] = false;
		break;
	}

	case WM_RBUTTONDOWN:
	{
		g_Window->GetMouse[wparam] = true;
		break;
	}

	case WM_RBUTTONUP:
	{
		g_Window->GetMouse[wparam] = false;
		break;
	}
	}

	return ::DefWindowProc(hwnd, msg, wparam, lparam);
}

void Window::Init(const std::string& appName)
{
	UNUSED(appName);

	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(wc));
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = TEXT("Simple Window Class");
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = &WndProc;

	::RegisterClassEx(&wc);

	RECT wr;
	wr.left = 0;
	wr.right = 1024;
	wr.top = 0;
	wr.bottom = 1024;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	WCHAR windowTitle[1024];
	MultiByteToWideChar(GetACP(), 0, appName.c_str(), -1, windowTitle, sizeof(windowTitle) / sizeof(windowTitle[0]));

	m_Hwnd = ::CreateWindowEx( WS_EX_OVERLAPPEDWINDOW , wc.lpszClassName, windowTitle, WS_OVERLAPPEDWINDOW | WS_SYSMENU, 0, 0, wr.right-wr.left, wr.bottom - wr.top, NULL, NULL, ::GetModuleHandle(NULL), NULL);

	::SetWindowLongPtr(reinterpret_cast<HWND>(m_Hwnd), GWLP_USERDATA, (LONG_PTR)this);

	::ShowWindow(reinterpret_cast<HWND>(m_Hwnd), SW_SHOW);
	::SetForegroundWindow(reinterpret_cast<HWND>(m_Hwnd));
	::SetFocus(reinterpret_cast<HWND>(m_Hwnd));
}

bool Window::RunMessagePump()
{
	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	g_Window->OnUpdate();

	Sleep(0);

	return true;
}

bool Window::Destroy()
{
	if (m_Hwnd == nullptr)
	{
		return true;
	}

	::DestroyWindow(reinterpret_cast<HWND>(m_Hwnd));

	m_Hwnd = nullptr;
	m_InputSystem = nullptr;

	return false;
}

void Window::OnUpdate()
{
	::UpdateWindow(reinterpret_cast<HWND>(m_Hwnd));
}

bool Window::IsAppQuiting()
{
	return m_IsQuitting;
}

void Window::SetTitle(const std::wstring& title)
{
	SetWindowText(reinterpret_cast<HWND>(m_Hwnd), title.c_str());
}

Window* Window::GetInstance()
{
	return g_Window;
}