#include "../PrecompiledHeaders/stdafx.h"
#include "Loader.h"

namespace tool
{
// Constructors and Destructor:

	Loader::Loader()
	{
	}

	Loader::~Loader()
	{
	}


// Functions:

	bool Loader::LoadObj(const std::string& filePath)
	{
		// If the file is not an .obj file return false.
		if (filePath.substr(filePath.size() - 4u, 4u) != ".obj")
		{
			return false;
		}

		std::ifstream inFile;

		inFile.open(filePath);

		if (!inFile.is_open())
		{
			return false;
		}

		LoadedMeshes.clear();
		LoadedVertices.clear();
		LoadedIndices.clear();

		std::vector<gfx::Vector3f> positions;
		std::vector<gfx::Vector2f> tCoords;
		std::vector<gfx::Vector3f> normals;

		std::vector<gfx::Vertex> vertices;
		std::vector<uint32>      indices;

		std::vector<std::string> meshMaterialNames;

		bool isListening = false;
		std::string meshName;

		gfx::Mesh tempMesh;

#ifdef OBJLOADING_CONSOLE_OUTPUT
		const uint32 outputEveryNth = 1000;
		uint32 outputIndicator = outputEveryNth;
#endif

		std::string curline;

		while (std::getline(inFile, curline))
		{
#ifdef OBJLOADING_CONSOLE_OUTPUT
			if ((outputIndicator = ((outputIndicator + 1) % outputEveryNth)) == 1)
			{
				if (!meshName.empty())
				{
					std::cout << "\r- " << meshName
						      << "\t| vertices: " << Positions.size()
							  << "\t| texcoords: " << TCoords.size()
						      << "\t| normals: " << Normals.size()
							  << "\t| triangles: " << (Vertices.size() / 3)
						      << (!MeshMaterialNames.empty() ? "\t| material: " + MeshMaterialNames.back() : "");
				}
			}
#endif
			// Generate a Mesh Object or prepare for an object to be created.
			if (FirstToken(curline) == "o" || FirstToken(curline) == "g" || curline[0] == 'g')
			{
				if (!isListening)
				{
					isListening = true;

					if (FirstToken(curline) == "o" || FirstToken(curline) == "g")
					{
						meshName = Tail(curline);
					}
					else
					{
						meshName = "unnamed";
					}
				}
			}
			else
			{
				// Generate a mesh to put into the array.
				if (!indices.empty() && !vertices.empty())
				{
					// Create mesh.
					tempMesh = gfx::Mesh(vertices, indices);
					tempMesh.MeshName = meshName;

					// Insert Mesh.
					LoadedMeshes.push_back(tempMesh);

					// Cleanup.
					vertices.clear();
					indices.clear();
					meshName.clear();

					meshName = Tail(curline);
				}
				// else...
				// https://github.com/Bly7/OBJ-Loader/blob/master/Source/OBJ_Loader.h
				// Line 521
			}
		}
	}
}