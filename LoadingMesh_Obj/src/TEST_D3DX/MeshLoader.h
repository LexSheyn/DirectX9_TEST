#ifndef MESHLOADER_H
#define MESHLOADER_H

#include "CacheEntry.h"
#include "Vertex3D.h"
#include "Material3D.h"
//#include "Mesh3D.h"

namespace test3d
{
	class MeshLoader
	{
	public:

	// Constructors and Destructor:

		MeshLoader();

		~MeshLoader();

	// Functions:

		HRESULT CreateMesh(IDirect3DDevice9* pd3dDevice, const std::string& strFileName);

		void    DestroyMesh();

	// Accessors:

		inline const uint32 GetNumberOfMaterials() const     { return m_Materials.size(); }
														     
		inline Material3D*  GetMaterial(uint32 index)        { return m_Materials.at(index); }
														     
		inline ID3DXMesh*   GetMesh()                        { return m_pMesh; }

		inline const std::string&  GetMediaDirectory() const { return m_strMediaDirectory; }

	// Modifiers:

		inline void SetMediaDirectory(const std::string& directory) { m_strMediaDirectory = directory; }

	private:

	// Private Functions:

		HRESULT LoadGeometryFronOBJ(const std::string& strFileName);

		HRESULT LoadMaterialsFromMTL(const std::string& strFileName);

		void    InitMaterial(Material3D* pMaterial);

		DWORD   AddVertex(uint32 hash, Vertex3D* pVertex);

		void    DeleteCache();

	// Variables:

		IDirect3DDevice9* m_pd3dDevice;

		ID3DXMesh* m_pMesh;

		std::vector<CacheEntry*> m_VertexCache;
		std::vector<Vertex3D>    m_Vertices;
		std::vector<DWORD>       m_Indices;
		std::vector<DWORD>       m_Attributes;
		std::vector<Material3D*> m_Materials;

		std::string m_strMediaDirectory;
	};
}

#endif // MESHLOADER_H