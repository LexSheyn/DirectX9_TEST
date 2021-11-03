#pragma once

#include "Window.h"

#include "../Updater/Updater.h"
#include "../RenderSystem/RenderSystem.h"

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

	HWND   m_hWnd;
	LPCSTR m_Title;
	int32  m_Width;
	int32  m_Height;

	dx9::Window  m_Window;

	dx9::Updater m_Updater;
			    
	dx9::RenderSystem m_RenderSystem;

// TEST
	dx9::TriangleShape m_Triangle;
};