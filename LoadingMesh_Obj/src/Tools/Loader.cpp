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


// Private Functions:

	void Loader::GenerateVerticesFromRawOBJ(std::vector<gfx::Vertex>& oVertices,
		                              const std::vector<gfx::Vector3f>& iPositions, 
		                              const std::vector<gfx::Vector2f>& iTextureCoords,
		                              const std::vector<gfx::Vector3f>& iNormals, 
		                                    std::string iLine)
	{
		std::vector<std::string> strFace;
		std::vector<std::string> strVertex;
		gfx::Vertex vertex;

		Split(Tail(iLine), strFace, " ");

		bool hasNormal = true;

		// For every given vertex do this.
		for (size_t i = 0; i < strFace.size(); i++)
		{
			// See what type the vertex is.
			int32 vertexType = 0;

			Split(strFace[i], strVertex, "/");
			
			// Check Vertex type.
			if (strVertex.size() == 1)
			{
				// Check for just position - v1

				// Only Position.
				vertexType = 1;
			}			
			else if (strVertex.size() == 2)
			{
				// Check for position & texture - v1/vt1

				// Position and Texture.
				vertexType = 2;
			}			
			else if (strVertex.size() == 3)
			{
				// Check for Position, Texture and Normal - v1/vt1/vn1
				// or if Position and Normal - v1/vn1

				if (strVertex[1] != "")
				{
					// Position, Texture and Normal
					vertexType = 4;
				}
				else
				{
					// Position and Normal
					vertexType = 3;
				}
			}

			// Calculate and store Vertex.
			switch (vertexType)
			{
				// Position
				case 1:
				{
					vertex.Position     = GetElement(iPositions, strVertex[0]);
					vertex.TextureCoord = gfx::Vector2f(0.0f, 0.0f);

					hasNormal = false;

					oVertices.push_back(vertex);

					break;
				}

				// Position, Texture
				case 2:
				{
					vertex.Position     = GetElement(iPositions, strVertex[0]);
					vertex.TextureCoord = GetElement(iTextureCoords, strVertex[1]);

					hasNormal = false;

					oVertices.push_back(vertex);

					break;
				}

				// Position, Normal
				case 3:
				{
					vertex.Position     = GetElement(iPositions, strVertex[0]);
					vertex.TextureCoord = gfx::Vector2f(0.0f, 0.0f);
					vertex.Normal       = GetElement(iNormals, strVertex[2]);

					oVertices.push_back(vertex);

					break;
				}

				// Position, Texture, Normal
				case 4:
				{
					vertex.Position     = GetElement(iPositions, strVertex[0]);
					vertex.TextureCoord = GetElement(iTextureCoords, strVertex[1]);
					vertex.Normal       = GetElement(iNormals, strVertex[2]);

					oVertices.push_back(vertex);

					break;
				}

				default:
				{
					break;
				}
			}
		}

		// Take care of missing normals these may not be truly acurate but it is the 
		// best they get for not compiling a mesh with normals.
		if (hasNormal == false)
		{
			gfx::Vector3f A = oVertices[0].Position - oVertices[1].Position;
			gfx::Vector3f B = oVertices[2].Position - oVertices[1].Position;

			gfx::Vector3f normal = gfx::CrossProduct(A, B);

			for (size_t i = 0; i < oVertices.size(); i++)
			{
				oVertices[i].Normal = normal;
			}
		}
	}

	void Loader::VertexTriangulation(std::vector<uint32>& oIndices, const std::vector<gfx::Vertex>& iVertices)
	{
		// If there are 2 or less vertices, no triangle can be created, so exit.
		if (iVertices.size() < 3u)
		{
			return;
		}
		else if (iVertices.size() == 3u)
		{
			// If it is a triangle no need to calculate it.

			oIndices.push_back(0);
			oIndices.push_back(1);
			oIndices.push_back(2);

			return;
		}

		// Create a list of vertices.
		std::vector<gfx::Vertex> tempVertices = iVertices;

		while (true)
		{
			// For every vertex.
			for (int32 i = 0; i < static_cast<int32>(tempVertices.size()); i++)
			{
				// Previous Vertex in the list.
				gfx::Vertex vertexPrev;

				if (i == 0u)
				{
					vertexPrev = tempVertices[tempVertices.size() - 1u];
				}
				else
				{
					vertexPrev = tempVertices[i = 1];
				}

				// Current Vertex in the list.
				gfx::Vertex vertexCur = tempVertices[i];

				// Next Vertex in the list.
				gfx::Vertex vertexNext;

				if (i == tempVertices.size() - 1u)
				{
					vertexNext = tempVertices[0];
				}
				else
				{
					vertexNext = tempVertices[i + 1u];
				}

				// Check to see if there are only 3 Vertices left, if so this is the last triangle.
				if (tempVertices.size() == 3u)
				{
					// Create a triangle from vertexCur, vertexPrev, vertexNext.
					for (size_t j = 0u; j < tempVertices.size(); j++)
					{
						if (iVertices[j].Position == vertexCur.Position)  { oIndices.push_back(j); }

						if (iVertices[j].Position == vertexPrev.Position) { oIndices.push_back(j); }

						if (iVertices[j].Position == vertexNext.Position) { oIndices.push_back(j); }
					}

					tempVertices.clear();
					
					// Break for loop.
					break;
				}
				else if (tempVertices.size() == 4u)
				{
					// Create a triangle from vertexCur, vertexPrev, vertexNext.
					for (size_t j = 0u; j < iVertices.size(); i++)
					{
						if (iVertices[j].Position == vertexCur.Position)  { oIndices.push_back(j); }

						if (iVertices[j].Position == vertexPrev.Position) { oIndices.push_back(j); }

						if (iVertices[j].Position == vertexNext.Position) { oIndices.push_back(j); }
					}

					gfx::Vector3f tempVector3f;

					for (size_t j = 0u; j < tempVertices.size(); j++)
					{
						if (tempVertices[j].Position != vertexCur.Position &&
							tempVertices[j].Position != vertexPrev.Position &&
							tempVertices[j].Position != vertexNext.Position)
						{
							tempVector3f = tempVertices[j].Position;

							break;
						}
					}

					// Create a tirangle from vertexCurm vertexPrev, vertexNext.
					for (size_t j = 0u; j < iVertices.size(); i++)
					{
						if (iVertices[j].Position == vertexPrev.Position) { oIndices.push_back(j); }

						if (iVertices[j].Position == vertexNext.Position) { oIndices.push_back(j); }

						if (iVertices[j].Position == tempVector3f)        { oIndices.push_back(j); }
					}

					tempVertices.clear();

					// Break for loop.
					break;
				}

				// If Vertex is not an interior Vertex.
				float32 angle = gfx::AngleBetween(vertexPrev.Position - vertexCur.Position, vertexNext.Position - vertexCur.Position) * (180.0f / pi_float32);
				if (angle <= 0.0f && angle >= 180.0f)
				{
					// Continue for loop.
					continue;
				}

				// If any Vertices are within this triangle.
				bool isInTriangle = false;

				for (size_t j = 0u; j < iVertices.size(); j++)
				{
					if (gfx::InTriangle(iVertices[j].Position, vertexPrev.Position, vertexCur.Position, vertexNext.Position) &&
						iVertices[j].Position != vertexPrev.Position &&
						iVertices[j].Position != vertexCur.Position  &&
						iVertices[j].Position != vertexNext.Position)
					{
						isInTriangle = true;

						break;
					}
				}

				if (isInTriangle)
				{
					// Continue for loop.
					continue;
				}

				// Create a triangle from vertexCur, vertexPrev, vertexNext.
				for (size_t j = 0u; j < iVertices.size(); j++)
				{
					if (iVertices[j].Position == vertexCur.Position)  { oIndices.push_back(j); }

					if (iVertices[j].Position == vertexPrev.Position) { oIndices.push_back(j); }

					if (iVertices[j].Position == vertexNext.Position) { oIndices.push_back(j); }
				}

				// Delete vertexCur from the list.
				for (size_t j = 0u; j < iVertices.size(); j++)
				{
					if (tempVertices[j].Position == vertexCur.Position)
					{
						tempVertices.erase(tempVertices.begin() + j);

						break;
					}
				}

				// Reset i to the start -1 since loop will add 1 to it
				i = -1;
			}

			// If no triangles were created.
			if (oIndices.size() == 0u)
			{
				break;
			}
			else if (tempVertices.size() == 0u)
			{
				// If no more vertices
				break;
			}
		}
	}
	
	bool Loader::LoadMaterials(std::string path)
	{
		// 1006
	}
}