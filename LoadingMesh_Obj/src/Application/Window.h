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

		bool GenerateWindow(HINSTANCE hInstance, int32_t nCmdShow, LPCSTR className, LPCSTR windowTitle, int32_t width, int32_t height, HWND& hWnd);
		bool GenerateWindow(HINSTANCE hInstance, int32_t nCmdShow, LPCSTR className, LPCSTR windowTitle, int32_t x, int32_t y, int32_t width, int32_t height, HWND& hWnd);

	private:

	// Variables:

	};
}
