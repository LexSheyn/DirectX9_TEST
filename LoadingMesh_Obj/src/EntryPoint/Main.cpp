#include "../PrecompiledHeaders/stdafx.h"

#include "../Application/Window.h"
#include "../Updater/Updater.h"
#include "../Renderer/Renderer.h"

int32_t __stdcall WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int32_t nCmdShow)
{
	HWND hWnd;

	dx9::Window window;

	if (window.GenerateWindow(hInstance, nCmdShow, "Win32Window", "D3DX9 Win32 Window", 800, 450, hWnd))
	{
		MSG msg;

		dx9::Updater updater;

		dx9::Renderer renderer;

		renderer.getDevice()->Initialize(hWnd, true);

		while (true)
		{
			while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);

				DispatchMessageA(&msg);
			}

			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				updater.Update(0.0f);

				renderer.Render();
			}
		}

		return static_cast<int32_t>(msg.wParam);
	}

	return 0;
}