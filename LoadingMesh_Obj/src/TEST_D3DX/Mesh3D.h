#ifndef MESH3D_H
#define MESH3D_H

#include "Vertex3D.h"
#include "Material3D.h"

namespace test3d
{
	class Mesh3D
	{
	public:

	// Constructors and Destructor:

		Mesh3D();

		~Mesh3D();

	// Functions:

		void Create(const std::vector<Vertex3D>& vertices,
		            const std::vector<uint32>& indices,
			                   IDirect3DDevice9* pd3dDevice);

		void Render(DWORD attribute);

	// Accessors:

		//

	// Modifiers:

		

	private:

	// Variables:

		ID3DXMesh* m_pMesh;

		std::string Name;

		std::vector<Vertex3D>           m_Vertices;
							            
		std::vector<uint32>             m_Indices;

		std::vector<uint32>             m_Attributes;
								        
		std::vector<Material3D>         m_Materials;

		std::vector<IDirect3DTexture9*> m_pTextures;

		// Effect???
	};
}

#endif // MESH3D_H
