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
	// Mesh:

		m_pMesh->Release();
		m_pMesh = nullptr;

	// Textures:

		for (auto& texture : m_pTextures)
		{
			texture->Release();
			texture = nullptr;
		}
	}


// Functions:

	void Mesh3D::Create(const std::vector<Vertex3D>& vertices,
		                const std::vector<uint32>& indices,
			                       IDirect3DDevice9* pd3dDevice)
	{
	// Create mesh:

		D3DXCreateMesh(m_Indices.size() / 3u, m_Vertices.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX_DECL, pd3dDevice, &m_pMesh);

	// Cope Vertex data:

		Vertex3D* p_vertex;

		m_pMesh->LockVertexBuffer( 0, (void**)&p_vertex );

		std::memcpy(p_vertex, m_Vertices.data(), m_Vertices.size() * sizeof(Vertex3D));

		m_pMesh->UnlockVertexBuffer();

	// Copy Index data:

		uint32* p_index;

		m_pMesh->LockIndexBuffer( 0, (void**)&p_index );

		std::memcpy(p_index, m_Indices.data(), m_Indices.size() * sizeof(Vertex3D));

		m_pMesh->UnlockIndexBuffer();

	// Copy Attributes data:

		DWORD* p_subset;

		m_pMesh->LockAttributeBuffer( 0, &p_subset );

		std::memcpy(p_subset, m_Attributes.data(), m_Attributes.size() * sizeof(DWORD));

		m_pMesh->UnlockAttributeBuffer();

	// Reorder the vertices according to subset and optimize the mesh for this graphics 
    // card's vertex cache. When rendering the mesh's triangle list the vertices will 
    // cache hit more often so it won't have to re-execute the vertex shader.

		// MeshLoader.cpp - 158
	}

	void Mesh3D::Render(DWORD attribute)
	{
		m_pMesh->DrawSubset(attribute);
	}

}