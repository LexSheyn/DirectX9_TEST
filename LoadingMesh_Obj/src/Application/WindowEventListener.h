#pragma once

namespace dx9
{
	class WindowEventListener
	{
	public:

		// Constuctors and Destructors:

		WindowEventListener();

		~WindowEventListener();

		// Functions:

		static LRESULT __stdcall WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}
