#include "../PrecompiledHeaders/stdafx.h"
#include "MeshLoader.h"

namespace dx9
{
// Constructors and Destructor:

	MeshLoader::MeshLoader()
	{
	}

	MeshLoader::~MeshLoader()
	{
	}


// Functions:

	bool MeshLoader::LoadObj(const std::string& filePath)
	{
		std::ifstream inFile;

		inFile.open(filePath);

		if (inFile.is_open())
		{
			std::string line;

			while (std::getline(inFile, line))
			{
				std::string text;

				inFile >> text;

				if (text == "v")
				{
					D3DXVECTOR3 vertex;

					inFile >> vertex.x;
					inFile >> vertex.y;
					inFile >> vertex.z;

					m_Vertices.push_back(vertex);
				}
				else if ( text == "vt")
				{
					ID3DXMesh* a;
					a = new ID3DXMesh();
				}
			}
		}
		else
		{
			MessageBoxA(nullptr, "Failed to open .obj", "LoadObj", NULL);
		}

		return true;
	}

}