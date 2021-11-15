#include "../PrecompiledHeaders/stdafx.h"

#include "../Application/Application.h"

int32 __stdcall WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int32 nCmdShow)
{
	Application application;

	application.Initialize(hInstance, nCmdShow);

	application.Run();

	return 0;
}