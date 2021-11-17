#include "../PrecompiledHeaders/stdafx.h"
#include "Mesh3D.h"

namespace test3d
{
	// Vertex declaration
	D3DVERTEXELEMENT9 VERTEX_DECL[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0},
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0},
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

// Constructors and Destructor:

	Mesh3D::Mesh3D()
	{
		m_pMesh = nullptr;
	}

	Mesh3D::~Mesh3D()
	{
		m_pMesh->Release();

		m_Name.clear();
		m_Vertices.clear();
		m_Indices.clear();
		m_Materials.clear();
		m_Textures.clear();
	}


// Functions:

	bool Mesh3D::Create(DWORD numFaces, DWORD numVertices, IDirect3DDevice9* pD3DDevice, ID3DXMesh** ppMesh)
	{
		// MeshLoader.cpp - 130

		return true;
	}

}