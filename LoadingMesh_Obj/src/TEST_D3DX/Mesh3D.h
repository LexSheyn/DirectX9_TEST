#ifndef MESH3D_H
#define MESH3D_H

#include "../TEST/Components/Vertex.h"

namespace test3d
{
	class Mesh3D
	{
	public:

	// Constructors and Destructor:

		Mesh3D();

		~Mesh3D();

	// Functions:

		bool Create(DWORD numFaces, DWORD numVertices, IDirect3DDevice9* pD3DDevice, ID3DXMesh** ppMesh);

	private:

	// Variables:

		ID3DXMesh* m_pMesh;

		std::string m_Name;

		std::vector<gfx::Vertex> m_Vertices;

		std::vector<uint32> m_Indices;

		std::vector<D3DMATERIAL9> m_Materials;

		std::vector<IDirect3DTexture9> m_Textures;
	};
}

#endif // MESH3D_H
