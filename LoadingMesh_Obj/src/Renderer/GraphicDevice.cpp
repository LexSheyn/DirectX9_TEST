#include "../PrecompiledHeaders/stdafx.h"
#include "GraphicDevice.h"

namespace dx9
{
// Constructors and Destructor:

	GraphicDevice::GraphicDevice()
	{
		// Device.
		m_Device   = nullptr;

		m_Direct3d = nullptr;

		m_d3dpp    = { 0 };

		m_Viewport = { 0 };

		// Vertexes.
		m_VB = nullptr;

		m_IB = nullptr;
	}
	
	GraphicDevice::~GraphicDevice()
	{
		if (m_Device)
		{
			m_Device->Release();
			m_Device = nullptr;
		}

		if (m_Direct3d)
		{
			m_Direct3d->Release();
			m_Direct3d = nullptr;
		}
	}
	

// Functions:

	bool GraphicDevice::Initialize(HWND hWnd, int32 width, int32 height, bool windowed)
	{
		// Create the Direct 3D Pointer.
		m_Direct3d = Direct3DCreate9(D3D_SDK_VERSION);

		if (!m_Direct3d)
		{
			return false;
		}

		ZeroMemory(&m_d3dpp, sizeof(D3DPRESENT_PARAMETERS));

		m_d3dpp.BackBufferWidth            = width;
		m_d3dpp.BackBufferHeight           = height;
		m_d3dpp.Windowed                   = windowed;
		m_d3dpp.BackBufferCount            = 1;
		m_d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
		m_d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
		m_d3dpp.MultiSampleQuality         = 0;		
		m_d3dpp.hDeviceWindow              = hWnd;
		m_d3dpp.Flags                      = 0;
		m_d3dpp.EnableAutoDepthStencil     = true;
		m_d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
		m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		m_d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
		m_d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;

		// Create the device.
		// D3DADAPTER_DEFAULT - Primary display adapter (default graphics card).
		// D3DDEVTYPE - Hardware rasterisation.
		// D3DCREATE_MIXED_VERTEXPROCESSING - Uses both hardware and software for 3D calculations.
		m_Direct3d->CreateDevice(D3DADAPTER_DEFAULT,
			                     D3DDEVTYPE_HAL,
		                         hWnd,
		                         D3DCREATE_MIXED_VERTEXPROCESSING,
			                     &m_d3dpp,
			                     &m_Device);

		if (!m_Device)
		{
			return false;
		}

		// Create viewport.
		ZeroMemory(&m_Viewport, sizeof(D3DVIEWPORT9));

		m_Viewport.X      = 0;
		m_Viewport.Y      = 0;
		m_Viewport.Width  = width;
		m_Viewport.Height = height;
		m_Viewport.MinZ   = 0;
		m_Viewport.MaxZ   = 1;
		
		m_Device->SetViewport(&m_Viewport);

		return true;
	}
	
	bool GraphicDevice::CreateVertexBuffer()
	{
		// TEST mesh
		Vertex verts[3] =
		{
			Vertex(0.0f,  0.0f, 0.0f, Color::Green),
			Vertex(1.0f,  0.0f, 0.0f, Color::Blue),
			Vertex(-1.0f, -1.0f, 0.0f, Color::Red)
		};

		// Create vertex buffer.
		m_Device->CreateVertexBuffer(3 * sizeof(Vertex), 0, Vertex::FVF, D3DPOOL_MANAGED, &m_VB, NULL);

		void* pVerts;
		m_VB->Lock(0, sizeof(verts), (void**)&pVerts, 0);
		std::memcpy(pVerts, &verts, sizeof(verts));
		m_VB->Unlock();

		return true;
	}

	void GraphicDevice::Clear(D3DCOLOR color)
	{
		// 2nd parameter is set to 'NULL' so that it clears  the entire back buffer.
		m_Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);
	}
	
	void GraphicDevice::Begin()
	{
		m_Device->BeginScene();
	}
	
	void GraphicDevice::End()
	{
		m_Device->EndScene();
	}
	
	void GraphicDevice::Present()
	{
		// Present scene to the window.
		m_Device->Present(NULL, NULL, NULL, NULL);
	}
}