#include "../PrecompiledHeaders/stdafx.h"
#include "Renderer.h"

namespace dx9
{
// Constructors and Destructor:

	Renderer::Renderer()
	{
		m_ScreenWidth  = 0;
		m_ScreenHeight = 0;
	}
	
	Renderer::~Renderer()
	{
	}
	

// Functions:

	void Renderer::Initialize(HWND hWnd, int32 width, int32 height, bool windowed)
	{
		m_GraphicDevice.Initialize(hWnd, width, height, windowed);

		m_ScreenWidth  = width;
		m_ScreenHeight = height;

		// Setup camera.
		m_Camera.SetDevice(m_GraphicDevice.GetDirect3DDevice());
		m_Camera.SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));

		// TEST position.
		D3DXVECTOR3 position = D3DXVECTOR3( 0.0f, 0.0f, -5.0f );
		D3DXVECTOR3 target   = D3DXVECTOR3( 0.0f, 0.0f,  1.0f );
		D3DXVECTOR3 up       = D3DXVECTOR3( 0.0f, 1.0f,  0.0f );

		m_Camera.SetPosition(position, target, up);
	}

	void Renderer::Render()
	{
		m_GraphicDevice.Clear(Color::Black);

		m_GraphicDevice.Begin();

		m_GraphicDevice.End();

		m_GraphicDevice.Present();
	}


// Accessors:

	GraphicDevice& Renderer::GetGraphicDevice()
	{
		return m_GraphicDevice;
	}
	
	Camera& Renderer::GetCamera()
	{
		return m_Camera;
	}
}