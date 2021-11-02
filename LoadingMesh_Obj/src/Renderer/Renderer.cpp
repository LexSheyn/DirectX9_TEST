#include "../PrecompiledHeaders/stdafx.h"
#include "Renderer.h"

namespace dx9
{
// Constructors and Destructor:

	Renderer::Renderer()
	{
		m_Device = new GraphicDevice();
	}
	
	Renderer::~Renderer()
	{
	}
	

// Functions:

	void Renderer::Render()
	{
		m_Device->Clear(D3DCOLOR_XRGB(0, 100, 100));

		m_Device->Begin();

		m_Device->End();

		m_Device->Present();
	}


// Accessors:

	GraphicDevice* Renderer::getDevice() const
	{
		return m_Device;
	}
}