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

		//

	private:

	// Variables:

		ID3DXMesh* pMesh;

		std::vector<gfx::Vertex> m_Vertices;

		std::vector<uint32> m_Indices;

		std::vector<D3DMATERIAL9> m_Materials;

		std::vector<IDirect3DTexture9> m_Textures;
	};
}

#endif // MESH3D_H
