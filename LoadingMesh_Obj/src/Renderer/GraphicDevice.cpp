#include "../PrecompiledHeaders/stdafx.h"
#include "GraphicDevice.h"

namespace dx9
{
// Constructors and Destructor:

	GraphicDevice::GraphicDevice()
	{
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

	void GraphicDevice::Initialize(HWND hWnd, bool windowed)
	{
		// Create the Direct 3D Pointer.
		m_Direct3d = Direct3DCreate9(D3D_SDK_VERSION);

		D3DPRESENT_PARAMETERS presentationParameters;
		ZeroMemory(&presentationParameters, sizeof(presentationParameters));
		presentationParameters.Windowed = windowed;
		presentationParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		presentationParameters.hDeviceWindow = hWnd;

		// Create the device.
		// D3DADAPTER_DEFAULT - Primary display adapter (default graphics card).
		// D3DDEVTYPE - Hardware rasterisation.
		// D3DCREATE_MIXED_VERTEXPROCESSING - Uses both hardware and software for 3D calculations.
		m_Direct3d->CreateDevice(D3DADAPTER_DEFAULT,
			                     D3DDEVTYPE_HAL,
		                         hWnd,
		                         D3DCREATE_MIXED_VERTEXPROCESSING,
			                     &presentationParameters,
			                     &m_Device);
	}
	
	void GraphicDevice::Clear(D3DCOLOR color)
	{
		// 2nd parameter is set to 'NULL' so that it clears  the entire back buffer.
		m_Device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
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