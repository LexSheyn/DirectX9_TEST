#pragma once

#include "../RenderObject/2D/TriangleShape.h"
#include "../RenderObject/2D/RectangleShape.h"
#include "../RenderObject/3D/SCube.h"

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

		// REPLACE TriangleShape by Shape, AND ALSO REWORK Shape AND HERITOR CLASSES
		bool CreateVertexBuffer(SCube* cube);

		bool CreateIndexBuffer(SCube* cube);
		
		void ClearBeginEndPresent(D3DCOLOR color);

	// Accessors:

		IDirect3DDevice9* GetDirect3DDevice();

		D3DXMATRIX* GetSceneMatrix();

		D3DXMATRIX* GetRotationMatrix_X();

		D3DXMATRIX* GetRotationMatrix_Y();

		D3DXMATRIX* GetRotationMatrix_Z();

	private:

	// Variables:

		IDirect3D9*           m_Direct3d;
						      
		IDirect3DDevice9*     m_Device;

		D3DPRESENT_PARAMETERS m_d3dpp;

		D3DVIEWPORT9          m_Viewport;

	// Scene:

		D3DXMATRIX m_SceneMatrix;
		D3DXMATRIX m_RotationMatrix_X;
		D3DXMATRIX m_RotationMatrix_Y;
		D3DXMATRIX m_RotationMatrix_Z;
				
	// Buffers:

		IDirect3DVertexBuffer9* m_VertexBuffer;

		IDirect3DIndexBuffer9*  m_IndexBuffer;

		// TEST
		uint32 m_VerticesCount;
		uint32 m_IndicesCount;
		uint32 m_PrimitivesCount;

		float x;
		float y;
		float z;
	};
}
