#include "../PrecompiledHeaders/stdafx.h"
#include "Application.h"

// Constructors and Destructor:

Application::Application()
{
	m_hWnd   = nullptr;

	m_Title  = "D3DX9 Win32 Window";
	
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	m_Width  = static_cast<int32>(desktop.right)  / 2;
			 
	m_Height = static_cast<int32>(desktop.bottom) / 2;
}

Application::~Application()
{

}


// unctions:

bool Application::Initialize(HINSTANCE hInstance, int32 nCmdShow)
{
	// 1. Create Window.
	m_Window.GenerateWindow(hInstance, nCmdShow, "Win32Window", "D3DX9 Win32 Window", m_Width, m_Height, m_hWnd);

	// 2. Initialize Renderer.
	m_RenderSystem.Initialize(m_hWnd, m_Width, m_Height, true);

	// 3. Create vertex buffer for specific shape.
	m_RenderSystem.GetGraphicDevice().CreateVertexBuffer(m_Width, m_Height, m_Triangle);

	return true;
}

int32 Application::Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessageA(&msg);
		}
		else
		{
			m_Updater.Update(0.0f);

			m_RenderSystem.Render();
		}
	}

	return static_cast<int32>(msg.wParam);
}