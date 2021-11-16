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

		m_D3DPresentParameters = { 0 };

		m_Viewport = { 0 };

		b_HandleDeviceLost = false;
		b_DeviceLost       = false;

		// Vertexes.
		m_VertexBuffer = nullptr;
		m_IndexBuffer  = nullptr;

		// TEST
		m_VerticesCount   = 0;
		m_IndicesCount    = 0;
		m_PrimitivesCount = 0;
	}
	
	GraphicDevice::~GraphicDevice()
	{
		dx9::Release(m_Device);
		dx9::Release(m_Direct3d);
		dx9::Release(m_VertexBuffer);
		dx9::Release(m_IndexBuffer);
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

		ZeroMemory(&m_D3DPresentParameters, sizeof(D3DPRESENT_PARAMETERS));

		m_D3DPresentParameters.BackBufferWidth            = width;
		m_D3DPresentParameters.BackBufferHeight           = height;
		m_D3DPresentParameters.Windowed                   = windowed;
		m_D3DPresentParameters.BackBufferCount            = 1;
		m_D3DPresentParameters.BackBufferFormat           = D3DFMT_A8R8G8B8;
		m_D3DPresentParameters.MultiSampleType            = D3DMULTISAMPLE_NONE;
		m_D3DPresentParameters.MultiSampleQuality         = 0;		
		m_D3DPresentParameters.hDeviceWindow              = hWnd;
		m_D3DPresentParameters.Flags                      = 0;
		m_D3DPresentParameters.EnableAutoDepthStencil     = true;
		m_D3DPresentParameters.AutoDepthStencilFormat     = D3DFMT_D24S8;
		m_D3DPresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		m_D3DPresentParameters.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
		m_D3DPresentParameters.SwapEffect                 = D3DSWAPEFFECT_DISCARD;

		// Create the device.
		// D3DADAPTER_DEFAULT - Primary display adapter (default graphics card).
		// D3DDEVTYPE - Hardware rasterisation.
		// D3DCREATE_MIXED_VERTEXPROCESSING - Uses both hardware and software for 3D calculations.
		m_Direct3d->CreateDevice(D3DADAPTER_DEFAULT,
			                     D3DDEVTYPE_HAL,
		                         hWnd,
		                         D3DCREATE_MIXED_VERTEXPROCESSING,
			                     &m_D3DPresentParameters,
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
	
	bool GraphicDevice::CreateVertexBuffer(TNCube* cube)
	{
		m_VerticesCount   = cube->VerticesNumber;

		void* pVertices;

		m_Device->CreateVertexBuffer(cube->VerticesNumber * sizeof(TNVertex), 0, TNVertex::FVF, D3DPOOL_MANAGED, &m_VertexBuffer, nullptr);

		m_VertexBuffer->Lock(0, sizeof(cube->Vertices), (void**)&pVertices, 0);

		memcpy_s(pVertices, sizeof(cube->Vertices), cube->Vertices, sizeof(cube->Vertices));

		m_VertexBuffer->Unlock();

		return true;
	}

	bool GraphicDevice::CreateVertexBuffer(gfx::Mesh* mesh)
	{
		m_VerticesCount = mesh->Vertices.size();

		void* pVertices;

		m_Device->CreateVertexBuffer(m_VerticesCount * sizeof(gfx::Vertex), 0, gfx::Vertex::FVF, D3DPOOL_MANAGED, &m_VertexBuffer, nullptr);

		const uint32 array_size = mesh->Vertices.size();

		gfx::Vertex* vertex_array = new gfx::Vertex[array_size];

		for (uint32 i = 0u; i < array_size; i++)
		{
			vertex_array[i] = mesh->Vertices[i];
		}

		m_VertexBuffer->Lock(0, sizeof(vertex_array), (void**)&pVertices, 0);

		std::memcpy(pVertices, &vertex_array, sizeof(vertex_array));

		m_VertexBuffer->Unlock();

		return true;
	}

	bool GraphicDevice::CreateIndexBuffer(TNCube* cube)
	{
		m_IndicesCount    = cube->IndicesNumber;
		m_PrimitivesCount = m_IndicesCount / 3;

		void* pIndices;

		m_Device->CreateIndexBuffer(cube->IndicesNumber * sizeof(int32), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_IndexBuffer, nullptr);

		m_IndexBuffer->Lock(0, sizeof(cube->Indices), (void**)&pIndices, 0);

		memcpy_s(pIndices, sizeof(cube->Indices), cube->Indices, sizeof(cube->Indices));

		m_IndexBuffer->Unlock();
		
		return true;
	}

	bool GraphicDevice::CreateIndexBuffer(gfx::Mesh* mesh)
	{
		m_IndicesCount    = mesh->Indices.size();
		m_PrimitivesCount = m_IndicesCount / 3;

		void* pIndices;

		m_Device->CreateIndexBuffer(m_IndicesCount * sizeof(uint32), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_IndexBuffer, nullptr);

		const uint32 array_size = mesh->Indices.size();

		uint32* index_array = new uint32[array_size];

		for (uint32 i = 0u; i < array_size; i++)
		{
			index_array[i] = mesh->Indices[i];
		}

		m_IndexBuffer->Lock(0, sizeof(index_array), (void**)&pIndices, 0);

		std::memcpy(pIndices, &index_array, sizeof(index_array));

		m_IndexBuffer->Unlock();

		return true;
	}

	void GraphicDevice::InvalidateDevice()
	{

	}

	void GraphicDevice::RestoreDevice()
	{
	}

	void GraphicDevice::Clear(D3DCOLOR color)
	{
		// Clear scene with certain color.
		// 2nd parameter is set to 'nullptr' so that it clears the entire back buffer.
		m_Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);
	}

	void GraphicDevice::Begin(TNCube* cube)
	{
		// Begin scene.
		m_Device->BeginScene();

		// Render state.
		m_Device->SetRenderState(D3DRS_LIGHTING, true);
		m_Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		m_Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);

		// Set light.
		m_Device->SetLight(0, m_LightSource.GetD3DLight());
		m_Device->LightEnable(0, true);

		// Other stuff.
		m_Device->SetTexture(0, cube->GetTexture());
		m_Device->SetMaterial(cube->GetMaterial());		
		m_Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(TNVertex));
		m_Device->SetIndices(m_IndexBuffer);
		m_Device->SetFVF(TNVertex::FVF);
		
		// Draw indexed primitive.
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
	
	D3DXMATRIX* GraphicDevice::GetScaleMatrix()
	{
		return &m_ScaleMatrix;
	}
	
	D3DXMATRIX* GraphicDevice::GetTranslationMatrix()
	{
		return &m_TranslationMatrix;
	}
}