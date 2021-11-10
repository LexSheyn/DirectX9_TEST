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

		// Big names.
		std::vector<gfx::Vector3f> Positions;
		std::vector<gfx::Vector2f> TextureCoords;
		std::vector<gfx::Vector3f> Normals;

		std::vector<gfx::Vertex> Vertices;
		std::vector<uint32>      Indices;

		std::vector<std::string> MeshMaterialNames;

		// Small names.
		bool isListening = false;
		std::string meshName;

		gfx::Mesh tempMesh;

#ifdef OBJLOADING_CONSOLE_OUTPUT
		const uint32 outputEveryNth = 1000;
		uint32 outputIndicator = outputEveryNth;
#endif

		std::string line;

		while (std::getline(inFile, line))
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
			if (FirstToken(line) == "o" || FirstToken(line) == "g" || line[0] == 'g')
			{
				if (!isListening)
				{
					isListening = true;

					if (FirstToken(line) == "o" || FirstToken(line) == "g")
					{
						meshName = Tail(line);
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
				if (!Indices.empty() && !Vertices.empty())
				{
					// Create mesh.
					tempMesh = gfx::Mesh(Vertices, Indices);
					tempMesh.MeshName = meshName;

					// Insert Mesh.
					LoadedMeshes.push_back(tempMesh);

					// Cleanup.
					Vertices.clear();
					Indices.clear();
					meshName.clear();

					meshName = Tail(line);
				}
				else
				{
					if (FirstToken(line) == "o" || FirstToken(line) == "g")
					{
						meshName = Tail(line);
					}
					else
					{
						meshName = "unnamed";
					}
				}
			}
#ifdef OBJLOADING_CONSOLE_OUTPUT
			std::cout << std::endl;
			outputIndicator = 0;
#endif
		}

		// Generate a Vertex Position.
		if (FirstToken(line) == "v")
		{
			std::vector<std::string> positionString;
			gfx::Vector3f positionVector;

			Split(Tail(line), positionString, " ");

			positionVector.x = std::stof(positionString[0]);
			positionVector.y = std::stof(positionString[1]);
			positionVector.z = std::stof(positionString[2]);

			Positions.push_back(positionVector);
		}

		// Generate a Vertex Texture Coordinate.
		if (FirstToken(line) == "vt")
		{
			std::vector<std::string> textureString;
			gfx::Vector2f textureVector;

			Split(Tail(line), textureString, " ");

			textureVector.x = std::stof(textureString[0]);
			textureVector.y = std::stof(textureString[1]);

			TextureCoords.push_back(textureVector);
		}

		// Generate a Vertex Normal.
		if (FirstToken(line) == "vn")
		{
			std::vector<std::string> normalString;
			gfx::Vector3f normalVector;

			Split(Tail(line), normalString, " ");

			normalVector.x = std::stof(normalString[0]);
			normalVector.y = std::stof(normalString[1]);
			normalVector.z = std::stof(normalString[2]);

			Normals.push_back(normalVector);
		}

		// Generate a face (vertices and indices).
		if (FirstToken(line) == "f")
		{
			// Generate Vertex.
			std::vector<gfx::Vertex> vertexVector;

			GenerateVerticesFromRawOBJ(vertexVector, Positions, TextureCoords, Normals, line);

			// Add vertices.
			for (size_t i = 0; i < vertexVector.size(); i++)
			{
				Vertices.push_back(vertexVector[i]);

				LoadedVertices.push_back(vertexVector[i]);
			}
			
			std::vector<uint32> iIndices;

			VertexTriangulation(iIndices, vertexVector);

			// Add Indices.
			for (size_t i = 0; i < iIndices.size(); i++)
			{
				uint32 indexNumber = static_cast<uint32>(Vertices.size() - vertexVector.size()) + iIndices[i];
				Indices.push_back(indexNumber);

				indexNumber = static_cast<uint32>(LoadedVertices.size() - vertexVector.size()) + iIndices[i];
				LoadedIndices.push_back(indexNumber);
			}
		}

		// Get Mesh Material Name.
		if (FirstToken(line) == "usemtl")
		{
			MeshMaterialNames.push_back(Tail(line));

			// Create new Mesh, if Material changes within group.
			if (!Indices.empty() && !Vertices.empty())
			{
				// Create Mesh.
				tempMesh = gfx::Mesh(Vertices, Indices);
				tempMesh.MeshName = meshName;
				
				// 618
				// Change mesh name if it already exists in a loop.
				// isExixting = true to start first loop.
				bool isExisting = true;
				
				for (uint32 i = 0; isExisting == true; i++)
				{
					tempMesh.MeshName = meshName + "_" + std::to_string(i);

					for (auto& mesh : LoadedMeshes)
					{
						if (mesh.MeshName == tempMesh.MeshName)
						{
							isExisting = true;
							break;
						}
						else
						{
							isExisting = false;
						}
					}
				}

				// Insert Mesh.
				LoadedMeshes.push_back(tempMesh);

				// Cleanup.
				Vertices.clear();
				Indices.clear();
			}

#ifdef OBJLOADING_CONSOLE_OUTPUT
			outputIndicator = 0;
#endif

			// Load Materials.
			if (FirstToken(line) == "mtllib")
			{
				// Generate LoadedMaterial.
				//

				// Generate a path to the material file.
				std::vector<std::string> temp;

				Split(filePath, temp, "/");
				
				std::string pathToMaterials = "";

				if (temp.size() != 1)
				{
					for (size_t i = 0; i < temp.size(); i++)
					{
						pathToMaterials += temp[i] + "/";
					}
				}

				pathToMaterials += Tail(line);

#ifdef OBJLOADING_CONSOLE_OUTPUT
			std::cout << std::endl << "- find materials in: " << pathToMaterials << std::endl;
#endif

				// Load Materials.
				LoadMaterials(pathToMaterials);
			}
		}

#ifdef OBJLOADING_CONSOLE_OUTPUT
	std::cout << std::endl;
#endif

		// Deal with last mesh.		
		if (!Indices.empty() && !Vertices.empty())
		{
			// Create Mesh.
			tempMesh = gfx::Mesh(Vertices, Indices);
			tempMesh.MeshName = meshName;

			// Insert Mesh.
			LoadedMeshes.push_back(tempMesh);
		}

		inFile.close();

		// Set Materials for each Mesh.
		for (size_t i = 0; i < MeshMaterialNames.size(); i++)
		{
			std::string materialName = MeshMaterialNames[i];

			// Find corresponding material name in loaded materials when found copy material
			// variables into mesh material.
			for (size_t j = 0; j < LoadedMaterials.size(); j++)
			{
				if (LoadedMaterials[j].Name == materialName)
				{
					LoadedMeshes[i].MeshMaterial = LoadedMaterials[j];
					break;
				}
			}
		}

		if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty())
		{
			return false;
		}

		return true;
	}
}