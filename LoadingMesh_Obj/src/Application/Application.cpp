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

	m_Message = { 0 };

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
	//0. Load Mesh.
//	m_Loader.LoadObj("C:/Users/Admin/Desktop/ttt2/tttt.obj");

//	m_Mesh = m_Loader.GetLoadedMeshes()[1];

	// 1. Create Window.
	m_Window.GenerateWindow(hInstance, nCmdShow, "Win32Window", "D3DX9 Win32 Window", m_Width, m_Height, m_hWnd);

	// 2. Initialize Renderer.
	m_RenderSystem.Initialize(m_hWnd, m_Width, m_Height, true);	

	// 3. Create vertex buffer for specific object.
	m_RenderSystem.GetGraphicDevice().CreateVertexBuffer(&m_TextureNormalCube);
//	m_RenderSystem.GetGraphicDevice().CreateVertexBuffer(&m_Mesh);
	
	// 4. Create index buffer for specific object.
	m_RenderSystem.GetGraphicDevice().CreateIndexBuffer(&m_TextureNormalCube);
//	m_RenderSystem.GetGraphicDevice().CreateIndexBuffer(&m_Mesh);

//	m_TexturedCube.SetTexture(m_RenderSystem.GetGraphicDevice().GetDirect3DDevice(), L"..\\..\\Resources\\Images\\Test_Image_32x32.png");
	m_TextureNormalCube.SetTexture(m_RenderSystem.GetGraphicDevice().GetDirect3DDevice(), L"C:/Users/Admin/Desktop/Test_Image_100x100.png");

	return true;
}

int32 Application::Run()
{
	m_Message = { 0 };

	while (m_Message.message != WM_QUIT)
	{
		if (PeekMessageA(&m_Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_Message);

			DispatchMessageA(&m_Message);
		}
		else
		{
			m_Updater.Update(0.01f);

			m_RenderSystem.Render(&m_TextureNormalCube, 0.01f);
		}

		// ~ 60 FPS
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}

	return static_cast<int32>(m_Message.wParam);
}

void Application::ShutDown()
{
	//
}
