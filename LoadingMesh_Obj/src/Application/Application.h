#pragma once

#include "Window.h"

#include "../Updater/Updater.h"
#include "../RenderSystem/RenderSystem.h"

#include "../TEST/Loader/Loader.h"

class Application
{
public:

// Constructors and Destructor:

	Application();

	virtual ~Application();

// Functions:

	bool Initialize(HINSTANCE hInstance, int32 nCmdShow);

	int32 Run();

	void ShutDown();

protected:

// Attributes:

	HWND   m_hWnd;
	LPCSTR m_Title;
	int32  m_Width;
	int32  m_Height;

	MSG m_Message;

	// Time.
	int64 m_TimeBegin;
	int64 m_TimeEnd;
	float  m_DeltaTime;
	
	dx9::Window  m_Window;

	dx9::Updater m_Updater;
			    
	dx9::RenderSystem m_RenderSystem;

	test::Loader m_Loader;

// TEST
//	dx9::TriangleShape m_Triangle;
//	dx9::RectangleShape m_Rectangle;
//	dx9::SCube m_ShadedCube;
//	dx9::TCube m_TexturedCube;
	dx9::TNCube m_TextureNormalCube;
//	gfx::Mesh m_Mesh;
};