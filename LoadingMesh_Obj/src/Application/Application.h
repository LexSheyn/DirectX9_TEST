#pragma once

#include "Window.h"

#include "../Updater/Updater.h"
#include "../Renderer/Renderer.h"

namespace dx9
{
	class Application
	{
	public:

	// Constructors and Destructor:

		Application();

		virtual ~Application();

	// Functions:

		bool Initialize(HINSTANCE hInstance, int32 nCmdShow);

		int32 Run();

	protected:

	// Attributes:

		HWND        m_hWnd;
		LPCSTR      m_Title;
		int32       m_Width;
		int32       m_Height;

		Window      m_Window;

		Updater     m_Updater;
				    
		Renderer    m_Renderer;

	// TEST

		TriangleShape m_Triangle;
	};
}