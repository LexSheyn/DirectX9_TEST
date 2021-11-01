#pragma once

#include "WindowEventListener.h"

namespace dx9
{
	class Window
	{
	public:

	// Constructors and Destructor:

		Window();

		virtual ~Window();

	// Functions:

		static bool GenerateWindow(HINSTANCE hInstance, int32_t nCmdShow, LPCSTR className, LPCSTR windowTitle, int32_t width, int32_t height);
		static bool GenerateWindow(HINSTANCE hInstance, int32_t nCmdShow, LPCSTR className, LPCSTR windowTitle, int32_t x, int32_t y, int32_t width, int32_t height);

	private:

	// Variables:

	};
}
