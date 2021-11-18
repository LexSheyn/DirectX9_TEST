#include "../PrecompiledHeaders/stdafx.h"
#include "MeshLoader.h"

namespace test3d
{
// Vertex declaration:

	D3DVERTEXELEMENT9 VERTEX_DECL[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0},
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0},
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

// Constructors and Destructor:

	MeshLoader::MeshLoader()
	{
		m_pd3dDevice = nullptr;
		m_pMesh      = nullptr;
	}

	MeshLoader::~MeshLoader()
	{
		this->DestroyMesh();
	}


// Functions:

	HRESULT MeshLoader::CreateMesh(IDirect3DDevice9* pd3dDevice, const std::string& strFileName)
	{
		std::string str_file_path = m_strMediaDirectory + strFileName;

	// Clear temporary storages first:

		this->DestroyMesh();

	// Store the device pointer:

		m_pd3dDevice = pd3dDevice;

	// Load the vertex buffer, index buffer, and subset information from a file. In this case, 
    // an .obj file was chosen for simplicity, but it's meant to illustrate that ID3DXXMesh objects
    // can be filled from any mesh file format once the necessary data is extracted from file.

		this->LoadGeometryFronOBJ(strFileName);

	// Load Material Textures:

		for (size_t i_material = 0u; i_material < m_Materials.size(); i_material++)
		{
			Material3D* p_material = m_Materials.at(i_material);

			if (p_material->strTexture[0])
			{
			// Avoid loading the same texture twise:

				bool b_found = false;

				for (size_t x = 0u; x < i_material; x++)
				{
					Material3D* p_current_material = m_Materials.at(x);

					if (0 == std::strcmp(p_current_material->strTexture, p_material->strTexture))
					{
						b_found = true;

						p_material->pTexture = p_current_material->pTexture;

						break;
					}
				}

			// Not found, load the Texture:

				if (!b_found)
				{
					D3DXCreateTextureFromFileA(pd3dDevice, p_material->strTexture, &(p_material->pTexture));
				}
			}
		}

	// Create the encapsulated Mesh:

		ID3DXMesh* p_mesh = nullptr;

		D3DXCreateMesh(m_Indices.size() / 3u, m_Vertices.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX_DECL, pd3dDevice, &p_mesh);

	// Copy the Vertex data:

		Vertex3D* p_vertex = nullptr;

		p_mesh->LockVertexBuffer(0, (void**)&p_vertex);

		memcpy( p_vertex, m_Vertices.data(), m_Vertices.size() * sizeof(Vertex3D));

		p_mesh->UnlockVertexBuffer();

		m_Vertices.clear();

	// Copy Index data:

		DWORD* p_index = nullptr;

		p_mesh->LockIndexBuffer( 0, (void**)&p_index);

		memcpy( p_index, m_Indices.data(), m_Indices.size() * sizeof (DWORD) );

		p_mesh->UnlockIndexBuffer();

		m_Indices.clear();

	// Copy Attribute data:

		DWORD* p_subset = nullptr;

		p_mesh->LockAttributeBuffer( 0, &p_subset);

		memcpy( p_subset, m_Attributes.data(), m_Attributes.size() * sizeof(DWORD) );

		p_mesh->UnlockAttributeBuffer();

		m_Attributes.clear();

	// Reorder the Vertices according to subset and optimaze the Mesh for this graphic card's Vertex cache.
	// When rendering the mesh's triangle list the vertices will cache hit more often so it will not have to
	// re-execute the Vertex shader.

		DWORD* adjacency = new DWORD[p_mesh->GetNumFaces() * 3u];

		if (adjacency == nullptr)
		{
			return E_OUTOFMEMORY;
		}

		p_mesh->GenerateAdjacency( 1e-6f, adjacency );

		p_mesh->OptimizeInplace( D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, adjacency, nullptr, nullptr, nullptr );

		delete[] adjacency;

		m_pMesh = p_mesh;

		return S_OK;
	}

	void MeshLoader::DestroyMesh()
	{
		for (size_t i_material = 0u; i_material < m_Materials.size(); i_material++)
		{
			Material3D* p_material = m_Materials.at(i_material);

		// Avoid releasing the same texture twice:

			for (size_t x = i_material + 1u; x < m_Materials.size(); x++)
			{
				Material3D* p_current_material = m_Materials.at(x);

				if (p_material != nullptr)
				{
					if (p_current_material->pTexture == p_material->pTexture)
					{
						p_current_material->pTexture = nullptr;
					}
				}				

				p_material->pTexture->Release();
				p_material->pTexture = nullptr;

				delete p_material;
				p_material = nullptr;
			}
		}

		m_Materials.clear();

		m_Vertices.clear();

		m_Indices.clear();

	//	m_pMesh->Release();
		m_pMesh = nullptr;

		m_pd3dDevice = nullptr;
	}


// Private Functions:

	HRESULT MeshLoader::LoadGeometryFronOBJ(const std::string& strFileName)
	{
		std::string str_material_file_name;

		std::string str_file_path = m_strMediaDirectory + strFileName;

	// Create temporary storage for the input data. Once the data has been loaded into
	// a resonable format we can create a ID3DXMesh object and fill it with the mesh data.

		std::vector<D3DXVECTOR3> positions;
		std::vector<D3DXVECTOR3> normals;
		std::vector<D3DXVECTOR2> texture_coords;

	// The first subset uses the default Material:

		Material3D* p_material = new Material3D();

		if (p_material == nullptr)
		{
			return E_OUTOFMEMORY;
		}

		this->InitMaterial( p_material );

		strcpy_s( p_material->strName, MAX_PATH - 1, "default" );

		m_Materials.push_back( p_material );

		DWORD dw_current_subset = 0u;

	// File input:

		std::string str_command;

		std::ifstream in_file;

		in_file.open(str_file_path);

		if (!in_file)
		{
			return E_FAIL;
		}

		for (;;)
		{
			in_file >> str_command;

			if (!in_file)
			{
				break;
			}

			if (0 == std::strcmp(str_command.c_str(), "#"))
			{
				// Comment.
			}
			else if (0 == std::strcmp(str_command.c_str(), "v"))
			{
			// Vertex position:

				float32 x;
				float32 y;
				float32 z;

				in_file >> x >> y >> z;

				positions.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (0 == std::strcmp(str_command.c_str(), "vt"))
			{
			// Vertex texture coordinate:

				float32 u;
				float32 v;

				in_file >> u >> v;

				texture_coords.push_back(D3DXVECTOR2(u, v));
			}
			else if (0 == std::strcmp(str_command.c_str(), "vn"))
			{
			// Vertex normal:

				float32 x;
				float32 y;
				float32 z;

				in_file >> x >> y >> z;

				normals.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (0 == std::strcmp(str_command.c_str(), "f"))
			{
			// Face:

				uint32 i_position;
				uint32 i_normal;
				uint32 i_texture_coord;

				Vertex3D vertex;

				for (uint32 i_face = 0u; i_face < 3u; i_face++)
				{
					ZeroMemory(&vertex, sizeof(Vertex3D));

				// OBJ format uses 1-based arrays.

					in_file >> i_position;
					vertex.Position = positions[i_position - 1u];

					if ('/' == in_file.peek())
					{
						in_file.ignore();

						if ('/' != in_file.peek())
						{
						// Optional Texture coordinate:

							in_file >> i_texture_coord;

							vertex.TextureCoord = texture_coords[i_texture_coord - 1u];
						}

						if ('/' == in_file.peek())
						{
						// Optional Vertex normal:

							in_file >> i_normal;

							vertex.Normal = normals[i_normal - 1u];
						}
					}

				// If a duplicate Vertex does not exist, add this Vertex to the Vertices list.
				// Store the index in the Indices array. The Vertices and Indices lists will
				// eventially become the Vertex Buffer and Index Buffer for mesh.

					DWORD index = AddVertex(i_position, &vertex);

					if (index == (DWORD)-1)
					{
						return E_OUTOFMEMORY;
					}

					m_Indices.push_back(index);
				}

				m_Attributes.push_back(dw_current_subset);
			}
			else if (0 == std::strcmp(str_command.c_str(), "mtllib"))
			{
			// Material library:

				in_file >> str_material_file_name;
			}
			else if (0 == std::strcmp(str_command.c_str(), "usemtl"))
			{
			// Material:

				std::string str_name;

				in_file >> str_name;

				bool b_found = false;

				for (size_t i_material = 0u; i_material < m_Materials.size(); i_material++)
				{
					Material3D* p_current_material = m_Materials.at(i_material);

					if (0 == std::strcmp(p_current_material->strName, str_name.c_str()))
					{
						b_found = true;

						dw_current_subset = i_material;

						break;
					}
				}

				if (!b_found)
				{
					p_material = new Material3D();

					if (p_material == nullptr)
					{
						return E_OUTOFMEMORY;
					}

					dw_current_subset = m_Materials.size();

					this->InitMaterial(p_material);

					strcpy_s(p_material->strName, MAX_PATH - 1, str_name.c_str());

					m_Materials.push_back(p_material);
				}
			}
			else
			{
				// Unimplemented or unrecognized command.
			}

			in_file.ignore( 1000, '\n' );
		}

	// Cleanup.

		in_file.close();

		this->DeleteCache();

	// If an associated material file was found, read that in as well.

		if (str_material_file_name[0])
		{
			LoadMaterialsFromMTL(str_material_file_name);
		}

		return S_OK;
	}

	HRESULT MeshLoader::LoadMaterialsFromMTL(const std::string& strFileName)
	{
		std::string str_file_path = m_strMediaDirectory + strFileName;

	// File Input

		std::string str_command;

		std::ifstream in_file;

		in_file.open(str_file_path);

		if (!in_file)
		{
			return E_FAIL;
		}

		Material3D* p_material = nullptr;

		for (;;)
		{
			in_file >> str_command;

			if (!in_file)
			{
				break;
			}

			if (0 == std::strcmp(str_command.c_str(), "newmtl"))
			{
			// Switching active Materials:

				std::string str_name;

				in_file >> str_name;

				p_material = nullptr;

				for (size_t i = 0u; i < m_Materials.size(); i++)
				{
					Material3D* p_current_material = m_Materials.at(i);

					if (0 == std::strcmp(str_command.c_str(), str_name.c_str()))
					{
						p_material = p_current_material;

						break;
					}
				}
			}

		// The rest of the commands rely on an active Material:

			if (p_material == nullptr)
			{
				continue;
			}

			if (0 == std::strcmp(str_command.c_str(), "#"))
			{
				// Comment.
			}
			else if (0 == std::strcmp(str_command.c_str(), "Ka"))
			{
			// Ambient color:

				float32 r;
				float32 g;
				float32 b;

				in_file >> r >> g >> b;

				p_material->vAmbient = D3DXVECTOR3(r, g, b);
			}
			else if (0 == std::strcmp(str_command.c_str(), "Kd"))
			{
			// Diffuse color:

				float32 r;
				float32 g;
				float32 b;

				in_file >> r >> g >> b;

				p_material->vDiffuse = D3DXVECTOR3(r, g, b);
			}
			else if (0 == std::strcmp(str_command.c_str(), "Ks"))
			{
			// Specular color:

				float32 r;
				float32 g;
				float32 b;

				in_file >> r >> g >> b;

				p_material->vSpecular = D3DXVECTOR3(r, g, b);
			}
			else if (0 == std::strcmp(str_command.c_str(), "d") || 0 == std::strcmp(str_command.c_str(), "Tr"))
			{
			// Alpha:

				in_file >> p_material->fAlpha;
			}
			else if (0 == std::strcmp(str_command.c_str(), "Ns"))
			{
			// Shininess:

				in_file >> p_material->nShininess;
			}
			else if (0 == std::strcmp(str_command.c_str(), "illum"))
			{
			// Specular on/off:

				int32 illumination;

				in_file >> illumination;

				p_material->bSpecular = (illumination == 2);
			}
			else if (0 == std::strcmp(str_command.c_str(), "map_Kd"))
			{
			// Texture:

				in_file >> p_material->strTexture;
			}
			else
			{
				// unimplemented or unrecognized command.
			}

			in_file.ignore(1000, '\n');
		}

		in_file.close();

		return S_OK;
	}

	void MeshLoader::InitMaterial(Material3D* pMaterial)
	{
		ZeroMemory(pMaterial, sizeof(Material3D));

		pMaterial->vAmbient   = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
		pMaterial->vDiffuse   = D3DXVECTOR3(0.8f, 0.8f, 0.8f);
		pMaterial->vSpecular  = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pMaterial->nShininess = 0;
		pMaterial->fAlpha     = 1.0f;
		pMaterial->bSpecular  = false;
		pMaterial->pTexture   = nullptr;
	}

	DWORD MeshLoader::AddVertex(uint32 hash, Vertex3D* pVertex)
	{
	// If this vertex doesn't already exist in the Vertices list, create a new entry.
    // Add the index of the vertex to the Indices list.

		bool8 b_found_in_list = false;

		DWORD index = 0u;

	// Since it's very slow to check every element in the vertex list, a hashtable stores
    // vertex indices according to the vertex position's index as reported by the OBJ file.

		if (static_cast<uint32>(m_VertexCache.size()) > hash)
		{
			CacheEntry* p_entry = m_VertexCache.at(hash);

			while (p_entry != nullptr)
			{
				Vertex3D* p_cache_vertex = m_Vertices.data() + p_entry->Index;

			// If this Vertex is identical to the Vertex already in the list, simply
			// point the index buffer to the existing Vertex.

				if (0 == memcmp( pVertex, p_cache_vertex, sizeof(Vertex3D) ))
				{
					b_found_in_list = true;

					index = p_entry->Index;

					break;
				}

				p_entry = p_entry->pNext;
			}
		}

	// Vertex was not found in the list. Create a new entry, both within the Vertices list
	// and also within the hashtable cache.

		if (!b_found_in_list)
		{
		// Add to the Vertices list:

			index = m_Vertices.size();

			m_Vertices.push_back( *pVertex );

		// Add this to the hashtable:

			CacheEntry* p_new_entry = new CacheEntry();

			if (p_new_entry == nullptr)
			{
				return (DWORD)-1;
			}

			p_new_entry->Index = index;
			p_new_entry->pNext = nullptr;

		// Grow the cache if needed:

			while (static_cast<uint32>(m_VertexCache.size()) <= hash)
			{
				m_VertexCache.push_back(nullptr);
			}

		// Add to the end of the linked list:

			CacheEntry* p_current_entry = m_VertexCache.at(hash);

			if (p_current_entry == nullptr)
			{
			// This is the head element.

				m_VertexCache.insert(m_VertexCache.begin() + hash, p_new_entry);
			}
			else
			{
			// Find the tail:

				while (p_current_entry->pNext != nullptr)
				{
					p_current_entry = p_current_entry->pNext;
				}

				p_current_entry->pNext = p_new_entry;
			}
		}

		return index;
	}

	void MeshLoader::DeleteCache()
	{
	// Iterate through all the elements in the cache and subsequent linked lists:

		for (size_t i = 0u; m_VertexCache.size(); i++)
		{
			CacheEntry* p_entry = m_VertexCache.at(i);

			while (p_entry != nullptr)
			{
				CacheEntry* p_next = p_entry->pNext;

				delete p_entry;

				p_entry = nullptr;

				p_entry = p_next;
			}
		}

		m_VertexCache.clear();
	}

}