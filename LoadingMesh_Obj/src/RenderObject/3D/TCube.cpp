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

		// Front face
		Vertices[0] = TVertex( -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, Color::Red );
		Vertices[1] = TVertex(  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, Color::Red );
		Vertices[2] = TVertex( -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, Color::Red );
		Vertices[3] = TVertex(  1.0f, -1.0f, -1.0f, 1.0f, 1.0f, Color::Red );

		// Back face
		Vertices[4] = TVertex(  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, Color::Red );
		Vertices[5] = TVertex( -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, Color::Red );
		Vertices[6] = TVertex(  1.0f, -1.0f,  1.0f, 0.0f, 1.0f, Color::Red );
		Vertices[7] = TVertex( -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, Color::Red );
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

	void TCube::SetTexture(const char* filePath)
	{
		m_TexturePath = filePath;
	}

}