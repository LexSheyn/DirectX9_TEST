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
		m_VertexBuffer = nullptr;
		m_IndexBuffer  = nullptr;

		// TEST
		m_VerticesCount   = 0;
		m_IndicesCount    = 0;
		m_PrimitivesCount = 0;

		// TEST
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
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
	
	bool GraphicDevice::CreateVertexBuffer(SCube* cube)
	{
		m_VerticesCount   = cube->VerticesNumber;

		void* pVertices;

		m_Device->CreateVertexBuffer(cube->VerticesNumber * sizeof(Vertex), 0, Vertex::FVF, D3DPOOL_MANAGED, &m_VertexBuffer, nullptr);

		m_VertexBuffer->Lock(0, sizeof(cube->Vertices), (void**)&pVertices, 0);

		std::memcpy(pVertices, &cube->Vertices, sizeof(cube->Vertices));

		m_VertexBuffer->Unlock();

		return true;
	}

	bool GraphicDevice::CreateIndexBuffer(SCube* cube)
	{
		m_IndicesCount    = cube->IndicesNumber;
		m_PrimitivesCount = m_IndicesCount / 3;

		void* pIndices;

		m_Device->CreateIndexBuffer(cube->IndicesNumber * sizeof(int32), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_IndexBuffer, nullptr);

		m_IndexBuffer->Lock(0, sizeof(cube->Indices), (void**)&pIndices, 0);

		std::memcpy(pIndices, &cube->Indices, sizeof(cube->Indices));

		m_IndexBuffer->Unlock();

		return true;
	}

	void GraphicDevice::Clear(D3DCOLOR color)
	{
		// Clear scene with certain color.
		// 2nd parameter is set to 'nullptr' so that it clears the entire back buffer.
		m_Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);
	}

	void GraphicDevice::Begin()
	{
		// Begin scene.
		m_Device->BeginScene();

		// TEST
	//	x += 0.010f;
	//	y += 0.010f;
	//	z += 0.005f;
	//	D3DXMatrixRotationX(&m_RotationMatrix_X, x);
	//	D3DXMatrixRotationY(&m_RotationMatrix_Y, y);
	//	D3DXMatrixRotationZ(&m_RotationMatrix_Z, z);
	//	m_SceneMatrix = m_RotationMatrix_X * m_RotationMatrix_Y * m_RotationMatrix_Z;
	//	m_Device->SetTransform(D3DTS_WORLD, &m_SceneMatrix);


		m_Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(Vertex));
		m_Device->SetIndices(m_IndexBuffer);
		m_Device->SetFVF(Vertex::FVF);

		// TEST rectangle.
		m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_IndicesCount, 0, m_PrimitivesCount);
	}

	void GraphicDevice::End()
	{
		// End scene.
		m_Device->EndScene();
	}

	void GraphicDevice::Present()
	{
		// Present scene to the window.
		m_Device->Present(nullptr, nullptr, nullptr, nullptr);
	}
	

// Accessors:

	IDirect3DDevice9* GraphicDevice::GetDirect3DDevice()
	{
		return m_Device;
	}
	
	D3DXMATRIX* GraphicDevice::GetSceneMatrix()
	{
		return &m_SceneMatrix;
	}
	
	D3DXMATRIX* GraphicDevice::GetRotationMatrix_X()
	{
		return &m_RotationMatrix_X;
	}
	
	D3DXMATRIX* GraphicDevice::GetRotationMatrix_Y()
	{
		return &m_RotationMatrix_Y;
	}
	
	D3DXMATRIX* GraphicDevice::GetRotationMatrix_Z()
	{
		return &m_RotationMatrix_Z;
	}
}