#include "../PrecompiledHeaders/stdafx.h"

#include "../Application/Window.h"

int32_t __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int32_t nCmdShow)
{
	if (dx9::Window::GenerateWindow(hInstance, nCmdShow, "Win32Window", "D3DX9 Win32 Window", 1280, 720))
	{
		MSG msg;

		while (true)
		{
			while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);

				DispatchMessageA(&msg);
			}

			switch (msg.message)
			{
				case WM_QUIT:
				{
					//
				} break;
			}
		}

		return msg.wParam;
	}

	return 0;
}