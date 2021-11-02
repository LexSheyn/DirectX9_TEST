#include "../PrecompiledHeaders/stdafx.h"
#include "Window.h"

namespace dx9
{
// Constructors and Destructor:

	Window::Window()
	{
	}

	Window::~Window()
	{
	}


// Functions:

	bool Window::GenerateWindow(HINSTANCE hInstance, int32 nCmdShow, LPCSTR className, LPCSTR windowTitle, int32 width, int32 height, HWND& hWnd)
	{			
		return GenerateWindow(hInstance, nCmdShow, className, windowTitle, 
			                  (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
			                  (GetSystemMetrics(SM_CYSCREEN) - height) / 2, width, height, hWnd);
	}

	bool Window::GenerateWindow(HINSTANCE hInstance, int32 nCmdShow, LPCSTR className, LPCSTR windowTitle, int32 x, int32 y, int32 width, int32 height, HWND& hWnd)
	{
		WNDCLASSEXA wcex;

		ZeroMemory(&wcex, sizeof(WNDCLASSEX));
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WindowEventListener::WindowProc;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIconA(NULL, (LPCSTR)IDI_APPLICATION);
		wcex.hCursor = LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wcex.lpszClassName = className;
		wcex.hIconSm = LoadIconA(NULL, (LPCSTR)IDI_WINLOGO);

		if (!RegisterClassExA(&wcex))
		{
			return false;
		}

		hWnd = CreateWindowExA(NULL, className, windowTitle, WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, hInstance, NULL);

		ShowWindow(hWnd, nCmdShow);

		return true;
	}
}