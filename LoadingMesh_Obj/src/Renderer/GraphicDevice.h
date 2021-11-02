#pragma once

namespace dx9
{
	class GraphicDevice
	{
	public:

	// Constructors and Destructor:

		GraphicDevice();

		~GraphicDevice();

	// Functions:

		void Initialize(HWND hWnd, bool windowed);
		
		void Clear(D3DCOLOR color);

		void Begin();

		void End();

		void Present();

	// Public Variables:

		IDirect3DDevice9* m_Device;

	private:

	// Variables:

		IDirect3D9* m_Direct3d;
	};
}
