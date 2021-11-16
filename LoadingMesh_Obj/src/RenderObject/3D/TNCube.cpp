#include "../../PrecompiledHeaders/stdafx.h"
#include "TNCube.h"

namespace dx9
{
// Constructors and Destructor:

	TNCube::TNCube()
	{
		m_Texture = nullptr;

		m_TexturePath = "";

		// (0.0) -------- (0.1)
		//
		//
		//
		// (0.1) -------- (1.1)

		// Front face.
		Vertices[0]  = TNVertex( -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f );
		Vertices[1]  = TNVertex(  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f );
		Vertices[2]  = TNVertex( -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f );
		Vertices[3]  = TNVertex(  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f );

		// Back face.
		Vertices[4]  = TNVertex(  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f );
		Vertices[5]  = TNVertex( -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f );
		Vertices[6]  = TNVertex(  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f );
		Vertices[7]  = TNVertex( -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f );

		// Left face.
		Vertices[8]  = TNVertex( -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f );
		Vertices[9]  = TNVertex( -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f );
		Vertices[10] = TNVertex( -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f );
		Vertices[11] = TNVertex( -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f );

		// Right face.
		Vertices[12] = TNVertex(  1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f );
		Vertices[13] = TNVertex(  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f );
		Vertices[14] = TNVertex(  1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f );
		Vertices[15] = TNVertex(  1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f );

		// Top face.
		Vertices[16] = TNVertex( -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f );
		Vertices[17] = TNVertex(  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f );
		Vertices[18] = TNVertex( -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f );
		Vertices[19] = TNVertex(  1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f );

		// Bottom face.
		Vertices[20] = TNVertex(  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f );
		Vertices[21] = TNVertex( -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f );
		Vertices[22] = TNVertex(  1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f );
		Vertices[23] = TNVertex( -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f );

		m_Material.Ambient  = (D3DXCOLOR)Color::White;
		m_Material.Diffuse  = (D3DXCOLOR)Color::White;
		m_Material.Emissive = (D3DXCOLOR)Color::Black;
		m_Material.Specular = (D3DXCOLOR)Color::White;
		m_Material.Power    = 5.0f;
	}

	TNCube::~TNCube()
	{
		dx9::Release(m_Texture);
	}


// Functions:

	//


// Accessors:

	IDirect3DTexture9* TNCube::GetTexture()
	{
		return m_Texture;
	}

	D3DMATERIAL9* TNCube::GetMaterial()
	{
		return &m_Material;
	}


// Modifiers:

	void TNCube::SetTexture(IDirect3DDevice9* device, LPCWSTR filePath)
	{
		D3DXCreateTextureFromFileW(device, filePath, &m_Texture);
	}

}