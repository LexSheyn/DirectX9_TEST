#include "../../PrecompiledHeaders/stdafx.h"
#include "LoaderTest.h"

namespace test
{
// Constructors and Destructor:

	LoaderTest::LoaderTest()
	{
	}

	LoaderTest::~LoaderTest()
	{
	}


// Functions:

	bool LoaderTest::LoadObj(const std::string& filePath)
	{
		if (filePath.substr(filePath.size() - 4u, 4u) != ".obj")
		{
			std::cout << "ERROR::LoadObj::File format is not .obj" << std::endl;
			
			return false;
		}

		//////////////////////////////////////////
		// Temp section
		//////////////////////////////////////////
		std::vector<gfx::Vector3f> Positions;
		std::vector<gfx::Vector2f> TextureCoords;
		std::vector<gfx::Vector3f> Normals;

		std::vector<gfx::Vertex> Vertices;
		std::vector<unsigned int> Indices;

		std::vector<std::string> MaterialNames;
				
		std::string meshName = "unnamed";

		gfx::Mesh tempMesh;
		//////////////////////////////////////////

		std::ifstream inFile;

		inFile.open(filePath);

		if (inFile.is_open())
		{
			std::string line;

			while (std::getline(inFile, line))
			{
				if (str::Parser::FirstToken(line) == "o" || str::Parser::FirstToken(line) == "g")
				{
					// Generate a Mesh Object or Prepare for an object to be created.

					if (!Vertices.empty() && !Indices.empty())
					{
						tempMesh = gfx::Mesh(Vertices, Indices);
						tempMesh.MeshName = meshName;

						m_LoadedMeshes.push_back(tempMesh);

						Vertices.clear();
						Indices.clear();
						meshName.clear();
					}

					meshName = str::Parser::Tail(line);
				}
				else if (str::Parser::FirstToken(line) == "v")
				{
					// Generate a Vertex Position.

					std::vector<std::string> vertex_position_str;

					gfx::Vector3f vertex_position;

					str::Parser::Split(str::Parser::Tail(line), vertex_position_str, " ");

					vertex_position.x = std::stof(vertex_position_str[0]);
					vertex_position.y = std::stof(vertex_position_str[1]);
					vertex_position.z = std::stof(vertex_position_str[2]);

					Positions.push_back(vertex_position);
				}
				else if (str::Parser::FirstToken(line) == "vt")
				{
					// Generate a Vertex Texture Coordinate.

					std::vector<std::string> texture_coord_str;

					gfx::Vector2f texture_coord;

					str::Parser::Split(str::Parser::Tail(line), texture_coord_str, " ");

					texture_coord.x = std::stof(texture_coord_str[0]);
					texture_coord.y = std::stof(texture_coord_str[1]);

					TextureCoords.push_back(texture_coord);
				}
				else if (str::Parser::FirstToken(line) == "vn")
				{
					// Generate a Vertex Normal.

					std::vector<std::string> vertex_normal_str;

					gfx::Vector3f vertex_normal;

					str::Parser::Split(str::Parser::Tail(line), vertex_normal_str, " ");

					vertex_normal.x = std::stof(vertex_normal_str[0]);
					vertex_normal.y = std::stof(vertex_normal_str[1]);
					vertex_normal.z = std::stof(vertex_normal_str[2]);

					Normals.push_back(vertex_normal);
				}
				else if (str::Parser::FirstToken(line) == "usemtl")
				{
					// Get Mesh Material name.

					MaterialNames.push_back(str::Parser::Tail(line));
				}
				else if (str::Parser::FirstToken(line) == "f")
				{
					// Generate a face (Vertices and Indices).

					std::vector<gfx::Vertex> temp_vertices;

					this->GenerateVerticesFromRawObj(temp_vertices, Positions, TextureCoords, Normals, line);

					// Add Vertices.

					for (size_t i = 0u; i < temp_vertices.size(); i++)
					{
						Vertices.push_back(temp_vertices[i]);

						m_LoadedVertices.push_back(temp_vertices[i]);
					}

					std::vector<uint32> iIndices;

					this->VertexTriangulation(iIndices, temp_vertices);

					// Add Indices.

					for (size_t i = 0u; i < iIndices.size(); i++)
					{
						uint32 index = Vertices.size() - temp_vertices.size() + iIndices[i];
						Indices.push_back(index);

						index = m_LoadedVertices.size() - temp_vertices.size() + iIndices[i];
						m_LoadedIndices.push_back(index);
					}

				}
				else if (str::Parser::FirstToken(line) == "mtllib")
				{
					// Generate a path to the Material file and load Material.

					std::vector<std::string> temp_str;

					std::string path_to_materials = "";

					str::Parser::Split(filePath, temp_str, "/");

					if (temp_str.size() != 1u)
					{
						for (size_t i = 0u; i < temp_str.size() - 1u; i++)
						{
							path_to_materials += temp_str[i] + "/";
						}
					}

					path_to_materials += str::Parser::Tail(line);

					this->LoadMaterials(path_to_materials);
				}
			}
		}

		inFile.close();

		return true;
	}


// Private Functions:

	void LoaderTest::GenerateVerticesFromRawObj(std::vector<gfx::Vertex>& oVertices, 
		                                  const std::vector<gfx::Vector3f>& iPositions, 
		                                  const std::vector<gfx::Vector2f>& iTextureCoords, 
		                                  const std::vector<gfx::Vector3f>& iNormals, 
		                                  const std::string& iLine)
	{
		std::vector<std::string> face_str;
		std::vector<std::string> vertex_str;

		gfx::Vertex vertex;

		str::Parser::Split(str::Parser::Tail(iLine), face_str, " ");

		bool hasNormal = true;

		// For every given Vertex.

		for (size_t i = 0u; i < face_str.size(); i++)
		{
			int32 vertex_type = 0;

			str::Parser::Split(face_str[i], vertex_str, "/");

			if (vertex_str.size() == 1u)
			{
				// Only Positiion - v1
				
				vertex_type = 1;
			}
			else if (vertex_str.size() == 2u)
			{
				// Position, Texture - v1/vt1

				vertex_type = 2;
			}
			else if (vertex_str.size() == 3u)
			{
				if (vertex_str[1] != "")
				{
					// Position, Texture, Normal - v1/vt1/vn1

					vertex_type = 4;
				}
				else
				{
					// Position, Normal

					vertex_type = 3;
				}
			}

			// Calculate and store the Vertex.

			switch (vertex_type)
			{
				// Position
				case 1:
				{
					vertex.Position     = str::Parser::GetElement(iPositions, vertex_str[0]);
					vertex.TextureCoord = gfx::Vector2f(0.0f, 0.0f);

					hasNormal = false;

					oVertices.push_back(vertex);

					break;
				}

				// Position, Texture
				case 2:
				{
					vertex.Position     = str::Parser::GetElement(iPositions, vertex_str[0]);
					vertex.TextureCoord = str::Parser::GetElement(iTextureCoords, vertex_str[1]);;

					hasNormal = false;

					oVertices.push_back(vertex);

					break;
				}

				// Position, Normal
				case 3:
				{
					vertex.Position     = str::Parser::GetElement(iPositions, vertex_str[0]);
					vertex.TextureCoord = gfx::Vector2f(0.0f, 0.0f);;
					vertex.Normal       = str::Parser::GetElement(iNormals, vertex_str[2]);

					oVertices.push_back(vertex);

					break;
				}

				// Position, Texture, Normal
				case 4:
				{
					vertex.Position     = str::Parser::GetElement(iPositions, vertex_str[0]);
					vertex.TextureCoord = str::Parser::GetElement(iTextureCoords, vertex_str[1]);
					vertex.Normal       = str::Parser::GetElement(iNormals, vertex_str[2]);

					oVertices.push_back(vertex);

					break;
				}

				default:
				{
					break;
				}
			}			
		}

		// Take care of missing Normals, these may not be truly acurate, but
		// it is the best they get for not compiling a mesh with Normals.

		if (hasNormal == false)
		{
			gfx::Vector3f A = oVertices[0].Position - oVertices[1].Position;
			gfx::Vector3f B = oVertices[2].Position - oVertices[1].Position;

			gfx::Vector3f normal = gfx::CrossProduct(A, B);

			for (size_t i = 0u; i < oVertices.size(); i++)
			{
				oVertices[i].Normal = normal;
			}
		}
	}

	void LoaderTest::VertexTriangulation(std::vector<uint32>& oIndices, 
		                           const std::vector<gfx::Vertex>& iVertices)
	{
		// If there are 2 or less verts no triangle can be created so exit.

		if (iVertices.size() < 3u)
		{
			return;
		}

		// If it is a triangle no need to calculate it.

		if (iVertices.size() == 3u)
		{
			oIndices.push_back(0);
			oIndices.push_back(1);
			oIndices.push_back(2);

			return;
		}

		// Create a list of Vertices.

		std::vector<gfx::Vertex> temp_vertices = iVertices;

		// For every Vertex.

		for (size_t i = 0u; i < temp_vertices.size(); i++)
		{
			// Previous Vertex ib the kust,

			gfx::Vertex vertex_previous;

			if (i == 0u)
			{
				vertex_previous = temp_vertices[temp_vertices.size() - 1u];
			}
			else
			{
				vertex_previous = temp_vertices[i - 1u];
			}

			// Current Vertex in the list.

			gfx::Vertex vertex_current;

			// Next Vertex in the lust.

			gfx::Vertex vertex_next;
			
			if (i == temp_vertices.size() - 1u)
			{
				vertex_next = temp_vertices[0];
			}
			else
			{
				vertex_next = temp_vertices[i + 1u];
			}

			// 890
		}
	}

	bool LoaderTest::LoadMaterials(const std::string& filePath)
	{


		return true;
	}

}