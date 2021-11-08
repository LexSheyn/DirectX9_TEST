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

	// Time.
	m_TimeBegin = 0;
	m_TimeEnd   = 0;
	m_DeltaTime = 0.018f;
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
	m_RenderSystem.GetGraphicDevice().CreateVertexBuffer(&m_ShadedCube);
	
	// 4. Create index buffer for specific shape.
	m_RenderSystem.GetGraphicDevice().CreateIndexBuffer(&m_ShadedCube);

	return true;
}

int32 Application::Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		m_TimeBegin = GetTickCount64();

		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessageA(&msg);
		}
		else
		{
			m_Updater.Update(0.01f);

			m_RenderSystem.Render(0.01f);
		}

		m_TimeEnd = GetTickCount64();

		m_DeltaTime = static_cast<float>(m_TimeEnd - m_TimeBegin);

		// ~ 60 FPS
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}

	return static_cast<int32>(msg.wParam);
}