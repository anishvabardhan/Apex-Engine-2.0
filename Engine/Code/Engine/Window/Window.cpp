#include "Window.h"
#include "Engine/Platform/WindowsH.h"
#include "Engine/Graphics/GLFunctions.h"

#pragma comment(lib, "opengl32.lib")

Window* g_Window = nullptr;
void* g_GLLibrary = NULL;

Window::Window()
	:m_IsRun(false), m_Hwnd(NULL), m_OurWindowHandleToDeviceContext(NULL), m_OurWindowHandleToRenderContext(NULL)
{
}

Window::~Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		g_Window->OnCreate(hwnd);
		break;
	}

	case WM_DESTROY:
	{
		g_Window->OnDestroy(g_Window->GetRenderContext());
		::PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		g_Window->GetKey[wparam] = true;
		break;
	}

	case WM_KEYUP:
	{
		g_Window->GetKey[wparam] = false;
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

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::Init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		return false;

	if (!g_Window)
		g_Window = this;

	m_Hwnd = nullptr;//::CreateWindowW( WS_EX_OVERLAPPEDWINDOW , L"MyWindowClass" , L"Apex2D" , WS_OVERLAPPEDWINDOW , 0 , 0 , 1024 , 1024 , NULL , NULL , ::GetModuleHandle(NULL) , NULL );

	if (!m_Hwnd)
		return false;

	::ShowWindow(reinterpret_cast<HWND>(m_Hwnd), SW_SHOW);

	m_IsRun = true;

	return true;
}

bool Window::Broadcast()
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

bool Window::Release()
{
	if (!::DestroyWindow(reinterpret_cast<HWND>(m_Hwnd)))
		return false;

	return true;
}

bool Window::IsRun()
{
	return m_IsRun;
}

void Window::SwappingBuffers()
{
	SwapBuffers(reinterpret_cast<HDC>(GetInstance()->GetDeviceContext()));
}

bool Window::MakeContextCurrent(void* hdc, void* hglrc)
{
	return wglMakeCurrent(reinterpret_cast<HDC>(hdc), reinterpret_cast<HGLRC>(hglrc));
}

void* Window::CreateOldRenderContext(void* hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;
	pfd.cStencilBits = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixel_format = ChoosePixelFormat(reinterpret_cast<HDC>(hdc), &pfd);
	if (pixel_format == NULL)
		return NULL;

	if (!SetPixelFormat(reinterpret_cast<HDC>(hdc), pixel_format, &pfd))
		return NULL;

	void* context = wglCreateContext(reinterpret_cast<HDC>(hdc));
	if (context == NULL)
		return NULL;

	return context;
}

void* Window::CreateRealRenderContext(void* hdc, int major, int minor)
{
	int const format_attribs[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,    
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,    
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,     
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 24,            			
		NULL, NULL,
	};

	size_t const MAX_PIXEL_FORMATS = 128;
	int formats[MAX_PIXEL_FORMATS];
	int pixel_format = 0;
	UINT format_count = 0;

	BOOL succeeded = wglChoosePixelFormatARB(reinterpret_cast<HDC>(hdc),
		format_attribs,
		nullptr,
		MAX_PIXEL_FORMATS,
		formats,
		(UINT*)&format_count);

	if (!succeeded) {
		return NULL;
	}

	for (unsigned int i = 0; i < format_count; ++i) {
		pixel_format = formats[i];
		succeeded = SetPixelFormat(reinterpret_cast<HDC>(hdc), pixel_format, NULL);
		if (succeeded) {
			break;
		}
		else {
			//DWORD error = GetLastError();
		}
	}

	if (!succeeded) {
		return NULL;
	}

	int context_flags = 0;
#if defined(_DEBUG)
	context_flags |= WGL_CONTEXT_DEBUG_BIT_ARB;
#endif

	int const attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major,                             
		WGL_CONTEXT_MINOR_VERSION_ARB, minor,                             
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,   
		WGL_CONTEXT_FLAGS_ARB, context_flags,                             
		0, 0
	};

	HGLRC context = wglCreateContextAttribsARB(reinterpret_cast<HDC>(hdc), NULL, attribs);
	if (context == NULL) {
		return NULL;
	}

	return context;
}


void Window::OnCreate(void* hwnd)
{
	g_GLLibrary = ::LoadLibraryA("opengl32.lib");
	m_OurWindowHandleToDeviceContext = GetDC(reinterpret_cast<HWND>(hwnd));
	
	HGLRC tempContext = reinterpret_cast<HGLRC>(CreateOldRenderContext(m_OurWindowHandleToDeviceContext));
	
	MakeContextCurrent(m_OurWindowHandleToDeviceContext, m_OurWindowHandleToRenderContext);
	BindNewGLFunctions();

	HGLRC realContext = reinterpret_cast<HGLRC>(CreateRealRenderContext(m_OurWindowHandleToDeviceContext, 4, 2));

	MakeContextCurrent(m_OurWindowHandleToDeviceContext, realContext);
	wglDeleteContext(tempContext);

	BindGLFunctions();

	m_OurWindowHandleToRenderContext = realContext;
}

void Window::OnUpdate()
{
	::UpdateWindow(reinterpret_cast<HWND>(m_Hwnd));
}

void Window::OnDestroy(void* rendercontext)
{
	m_IsRun = false;
	wglMakeCurrent(reinterpret_cast<HDC>(m_OurWindowHandleToDeviceContext), NULL);
	wglDeleteContext(reinterpret_cast<HGLRC>(rendercontext));
	if (!ReleaseDC(reinterpret_cast<HWND>(m_Hwnd), reinterpret_cast<HDC>(m_OurWindowHandleToDeviceContext)))
		MessageBox(reinterpret_cast<HWND>(m_Hwnd), L"Cannot Release !!", L"ERROR!!", MB_OK);

	FreeLibrary((HMODULE)g_GLLibrary);
}

Window* Window::GetInstance()
{
	return g_Window;
}