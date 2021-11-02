#pragma once

// TEST
#include "../Mesh/Vertex.h"

namespace dx9
{
	class GraphicDevice
	{
	public:

	// Constructors and Destructor:

		GraphicDevice();

		~GraphicDevice();

	// Functions:

		bool Initialize(HWND hWnd, int32 width, int32 height, bool windowed);

		// TEST
		bool CreateVertexBuffer();
		
		void Clear(D3DCOLOR color);

		void Begin();

		void End();

		void Present();

	private:

	// Variables:

		IDirect3D9*           m_Direct3d;
						      
		IDirect3DDevice9*     m_Device;

		D3DPRESENT_PARAMETERS m_d3dpp;

		D3DVIEWPORT9          m_Viewport;

		// TEST
		IDirect3DVertexBuffer9* m_VB;
		IDirect3DIndexBuffer9*  m_IB;
	};
}
