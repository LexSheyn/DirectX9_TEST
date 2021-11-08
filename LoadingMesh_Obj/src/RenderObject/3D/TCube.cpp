#include "../../PrecompiledHeaders/stdafx.h"
#include "TCube.h"

namespace dx9
{
// Constructors and Destructor:


	TCube::TCube()
	{
		m_Texture = nullptr;

		m_TexturePath = "";

		// (0.0) -------- (0.1)
		//
		//
		//
		// (0.1) -------- (1.1)

		// Front face.
		Vertices[0] = TVertex( -1.0f,  1.0f, -1.0f, 0.0f, 0.0f );
		Vertices[1] = TVertex(  1.0f,  1.0f, -1.0f, 1.0f, 0.0f );
		Vertices[2] = TVertex( -1.0f, -1.0f, -1.0f, 0.0f, 1.0f );
		Vertices[3] = TVertex(  1.0f, -1.0f, -1.0f, 1.0f, 1.0f );

		// Back face.
		Vertices[4] = TVertex(  1.0f,  1.0f,  1.0f, 0.0f, 0.0f );
		Vertices[5] = TVertex( -1.0f,  1.0f,  1.0f, 1.0f, 0.0f );
		Vertices[6] = TVertex(  1.0f, -1.0f,  1.0f, 0.0f, 1.0f );
		Vertices[7] = TVertex( -1.0f, -1.0f,  1.0f, 1.0f, 1.0f );

		// Left face.
		Vertices[8]  = TVertex( -1.0f,  1.0f,  1.0f, 0.0f, 0.0f );
		Vertices[9]  = TVertex( -1.0f,  1.0f, -1.0f, 1.0f, 0.0f );
		Vertices[10] = TVertex( -1.0f, -1.0f,  1.0f, 0.0f, 1.0f );
		Vertices[11] = TVertex( -1.0f, -1.0f, -1.0f, 1.0f, 1.0f );

		// Right face.
		Vertices[12] = TVertex(  1.0f,  1.0f, -1.0f, 0.0f, 0.0f );
		Vertices[13] = TVertex(  1.0f,  1.0f,  1.0f, 1.0f, 0.0f );
		Vertices[14] = TVertex(  1.0f, -1.0f, -1.0f, 0.0f, 1.0f );
		Vertices[15] = TVertex(  1.0f, -1.0f,  1.0f, 1.0f, 1.0f );

		// Top face.
		Vertices[16] = TVertex( -1.0f,  1.0f,  1.0f, 0.0f, 0.0f );
		Vertices[17] = TVertex(  1.0f,  1.0f,  1.0f, 1.0f, 0.0f );
		Vertices[18] = TVertex( -1.0f,  1.0f, -1.0f, 0.0f, 1.0f );
		Vertices[19] = TVertex(  1.0f,  1.0f, -1.0f, 1.0f, 1.0f );

		// Bottom face.
		Vertices[20] = TVertex(  1.0f, -1.0f,  1.0f, 0.0f, 0.0f );
		Vertices[21] = TVertex( -1.0f, -1.0f,  1.0f, 1.0f, 0.0f );
		Vertices[22] = TVertex(  1.0f, -1.0f, -1.0f, 0.0f, 1.0f );
		Vertices[23] = TVertex( -1.0f, -1.0f, -1.0f, 1.0f, 1.0f );
	}

	TCube::~TCube()
	{
		dx9::Release(m_Texture);
	}


// Functions:

	//


// Accessors:

	const std::string& TCube::GetTexturePath() const
	{
		return m_TexturePath;
	}


// Modifiers:

	void TCube::SetPosition(D3DXVECTOR3 position)
	{
		m_Position = position;
	}

	void TCube::SetPosition(float x, float y, float z)
	{
		m_Position = D3DXVECTOR3(x, y, z);
	}

	void TCube::SetRotation(D3DXVECTOR3 rotation)
	{
		m_Rotation = rotation;
	}

	void TCube::SetRotation(float x, float y, float z)
	{
		m_Rotation = D3DXVECTOR3(x, y, z);
	}

	void TCube::SetScale(D3DXVECTOR3 scale)
	{
		m_Rotation = scale;
	}

	void TCube::SetScale(float x, float y, float z)
	{
		m_Rotation = D3DXVECTOR3(x, y, z);
	}

	void TCube::SetTexture(IDirect3DDevice9* device, LPCWSTR filePath)
	{
	//	m_TexturePath = filePath;

		if (D3DXCreateTextureFromFile(device, filePath, &m_Texture) == D3D_OK)
		{
			MessageBox(nullptr, L"D3D_OK", NULL, NULL);
		}
	}

}