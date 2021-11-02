#include "../PrecompiledHeaders/stdafx.h"
#include "Application.h"

namespace dx9
{
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
	

// Functions:

	bool Application::Initialize(HINSTANCE hInstance, int32 nCmdShow)
	{
		if (!m_Window.GenerateWindow(hInstance, nCmdShow, "Win32Window", "D3DX9 Win32 Window", m_Width, m_Height, m_hWnd))
		{
			return false;
		}

		if (!m_Renderer.getDevice()->Initialize(m_hWnd, m_Width, m_Height, true))
		{
			return false;
		}

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

				m_Renderer.Render();
			}
		}

		return static_cast<int32>(msg.wParam);
	}
}