#pragma once

#include "GraphicDevice.h"
#include "Camera.h"



namespace dx9
{
	class Renderer
	{
	public:

	// Constructors and Destructor:

		Renderer();

		~Renderer();

	// Functions:

		void Initialize(HWND hWnd, int32 width, int32 height, bool windowed);

		void Render();

	// Accessors:

		GraphicDevice& GetGraphicDevice();

		Camera& GetCamera();

	private:

	// Variables:

		GraphicDevice m_GraphicDevice;

		Camera        m_Camera;

		int32         m_ScreenWidth;
		int32         m_ScreenHeight;
	};
}
