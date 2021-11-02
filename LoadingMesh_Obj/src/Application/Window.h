#pragma once

#include "WindowEventListener.h"

#include "../Renderer/GraphicDevice.h"

namespace dx9
{
	class Window
	{
	public:

	// Constructors and Destructor:

		Window();

		virtual ~Window();

	// Functions:

		bool GenerateWindow(HINSTANCE hInstance, int32 nCmdShow, LPCSTR className, LPCSTR windowTitle, int32 width, int32 height, HWND& hWnd);
		bool GenerateWindow(HINSTANCE hInstance, int32 nCmdShow, LPCSTR className, LPCSTR windowTitle, int32 x, int32 y, int32 width, int32 height, HWND& hWnd);

	private:

	// Variables:

	};
}
