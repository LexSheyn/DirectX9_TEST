#include "../PrecompiledHeaders/stdafx.h"
#include "WindowEventListener.h"

namespace dx9
{
// Constructors and Destructor:

	WindowEventListener::WindowEventListener()
	{
	}

	WindowEventListener::~WindowEventListener()
	{
	}


// Functions:

	LRESULT __stdcall WindowEventListener::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_CLOSE:
			{
				DestroyWindow(hWnd);

				return 0;
			}

			case WM_DESTROY:
			{
				PostQuitMessage(0);

				return 0;
			}
		}

		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
}