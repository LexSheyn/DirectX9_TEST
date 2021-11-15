#include "../../PrecompiledHeaders/stdafx.h"
#include "Loader.h"

namespace test
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
				
		bool isFirstMesh = true;

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
					if (isFirstMesh)
					{
						isFirstMesh = false;

						meshName = str::Parser::Tail(line);
					}
					else
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

							meshName = str::Parser::Tail(line);
						}
						else
						{
							meshName = str::Parser::Tail(line);
						}
					}					
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
				else if (str::Parser::FirstToken(line) == "usemtl")
				{
					// Get Mesh Material name.

					MaterialNames.push_back(str::Parser::Tail(line));
// TEST -- Begin
					// Create new Mesh, if Material changes within a group
					if (!Vertices.empty() && !Indices.empty())
					{
						// Create Mesh
						tempMesh = gfx::Mesh(Vertices, Indices);

						tempMesh.MeshName = meshName;
						
						// TEST
						bool isExisting = false;

						for (uint32 i = 0u; isExisting; i++)
						{
							tempMesh.MeshName = meshName + "_" + std::to_string(i);

							for (auto& mesh : m_LoadedMeshes)
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

						// Insert Mesh
						m_LoadedMeshes.push_back(tempMesh);

						// Cleanup
						Vertices.clear();
						Indices.clear();
					}
// TEST -- End
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

			// Deal with last mesh.

			if (!Vertices.empty() && !Indices.empty())
			{
				// Create Mesh.

				tempMesh = gfx::Mesh(Vertices, Indices);
				tempMesh.MeshName = meshName;

				// Insert Mesh.

				m_LoadedMeshes.push_back(tempMesh);
			}
		}

		inFile.close();

		// Set Materials for each Mesh.

		for (size_t i = 0u; i < MaterialNames.size(); i++)
		{
			std::string material_name = MaterialNames[i];

			// Find corresponding material name in loaded materials
			// when found copy material variables into mesh material.

			for (size_t k = 0u; k < m_LoadedMaterials.size(); k++)
			{
				if (m_LoadedMaterials[k].Name == material_name)
				{
					m_LoadedMeshes[i].MeshMaterial = m_LoadedMaterials[k];

					break;
				}
			}		
		}

		if (m_LoadedMeshes.empty() && m_LoadedVertices.empty() && m_LoadedIndices.empty())
		{
			return false;
		}

		return true;
	}


// Accessors:

	std::vector<gfx::Mesh>& Loader::GetLoadedMeshes()
	{
		return m_LoadedMeshes;
	}

	std::vector<gfx::Vertex>& Loader::GetLoadedVertices()
	{
		return m_LoadedVertices;
	}

	std::vector<uint32>& Loader::GetLoadedIndices()
	{
		return m_LoadedIndices;
	}

	std::vector<gfx::Material>& Loader::GetLoadedMaterials()
	{
		return m_LoadedMaterials;
	}


// Private Functions:

	void Loader::GenerateVerticesFromRawObj(std::vector<gfx::Vertex>& oVertices, 
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

	void Loader::VertexTriangulation(std::vector<uint32>& oIndices, 
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

		for (int32 i = 0; i < static_cast<int32>(temp_vertices.size()); i++)
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

			// Check to see if there are only 3 vertices left so this is the last triangle.
			if (temp_vertices.size() == 3u)
			{
				// Create triangle from vertex_current, vertex_previous, vertex_next.

				for (size_t j = 0u; j < temp_vertices.size(); j++)
				{
					if (iVertices[j].Position == vertex_current.Position)  { oIndices.push_back(j); }
					
					if (iVertices[j].Position == vertex_previous.Position) { oIndices.push_back(j); }
					
					if (iVertices[j].Position == vertex_next.Position)     { oIndices.push_back(j); }
				}

				temp_vertices.clear();

				break;
			}
			else if (temp_vertices.size() == 4u)
			{
				// Create triangle from vertex_current, vertex_previous, vertex_next.

				for (size_t j = 0u; j < temp_vertices.size(); j++)
				{
					if (iVertices[j].Position == vertex_current.Position)  { oIndices.push_back(j); }
					
					if (iVertices[j].Position == vertex_previous.Position) { oIndices.push_back(j); }
					
					if (iVertices[j].Position == vertex_next.Position)     { oIndices.push_back(j); }
				}

				gfx::Vector3f temp_vector;

				for (size_t j = 0u; j < iVertices.size(); j++)
				{
					if (temp_vertices[j].Position != vertex_current.Position &&
						temp_vertices[j].Position != vertex_previous.Position &&
						temp_vertices[j].Position != vertex_next.Position)
					{
						temp_vector = temp_vertices[j].Position;

						break;
					}
				}

				// Create triangle from vertex_current, vertex_previous, vertex_next.

				for (size_t j = 0u; j < iVertices.size(); j++)
				{										
					if (iVertices[j].Position == vertex_previous.Position) { oIndices.push_back(j); }
					
					if (iVertices[j].Position == vertex_next.Position)     { oIndices.push_back(j); }

					if (iVertices[j].Position == temp_vector)              { oIndices.push_back(j); }
				}

				temp_vertices.clear();

				break;
			}

			// 948
			// If Vertex in not an interior Vertex.

			float32 angle = gfx::AngleBetween(vertex_previous.Position - vertex_current.Position, (vertex_next.Position - vertex_current.Position) * (180.0f / Pi_float32));

			if (angle <= 0.0f || angle >= 180.0f)
			{
				continue;
			}

			// If any Vertex are within this triangle.

			bool isInTriangle = false;

			for (size_t j = 0u; j < iVertices.size(); j++)
			{
				if (gfx::InTriangle(iVertices[j].Position, vertex_previous.Position, vertex_current.Position, vertex_next.Position) &&
					iVertices[j].Position != vertex_previous.Position &&
					iVertices[j].Position != vertex_current.Position &&
					iVertices[j].Position != vertex_next.Position)
				{
					isInTriangle = true;

					break;
				}
			}

			if (isInTriangle == true)
			{
				continue;
			}

			// Create triangle from vertex_current, vertex_previous, vertex_next.

			for (size_t j = 0u; j < iVertices.size(); j++)
			{										
				if (iVertices[j].Position == vertex_current.Position)  { oIndices.push_back(j); }
				
				if (iVertices[j].Position == vertex_previous.Position) { oIndices.push_back(j); }

				if (iVertices[j].Position == vertex_next.Position)     { oIndices.push_back(j); }
			}

			// Delete vertex_current from the list.

			for (size_t j = 0u; j < temp_vertices.size(); j++)
			{
				if (temp_vertices[j].Position == vertex_current.Position)
				{
					temp_vertices.erase(temp_vertices.begin() + j);

					break;
				}
			}

			// Reset i to the start -1 since loop will add 1 to it

			i = -1;
		}

		// If no thiangle were created.
		if (oIndices.size() == 0u)
		{
			return;
		}

		if (temp_vertices.size() == 0u)
		{
			return;
		}
	}

	bool Loader::LoadMaterials(const std::string& filePath)
	{
		// If the file is not a material file return false.

		if (filePath.substr(filePath.size() - 4u, filePath.size()) != ".mtl")
		{
			return false;
		}

		std::ifstream inFile;

		inFile.open(filePath);

		if (inFile.is_open())
		{
			gfx::Material tempMaterial;

			bool isFirstMaterial = true;

			// Go through each line looking for Material variables.

			std::string line;

			while (std::getline(inFile, line))
			{
				// New Material and Material name.

				if (str::Parser::FirstToken(line) == "newmtl")
				{
					if (isFirstMaterial)
					{
						isFirstMaterial = false;

						if (line.size() > 7u)
						{
							tempMaterial.Name = str::Parser::Tail(line);
						}
						else
						{
							tempMaterial.Name = "none";
						}
					}
					else
					{
						// Generate the Material.

						// Push back loaded Material.

						m_LoadedMaterials.push_back(tempMaterial);

						// Clear loaded Material.

						tempMaterial = gfx::Material();

						if (line.size() > 7u)
						{
							tempMaterial.Name = str::Parser::Tail(line);
						}
						else
						{
							tempMaterial.Name = "none";
						}
					}
				}
				else if (str::Parser::FirstToken(line) == "Ka")
				{
					// Ambient Color.

					std::vector<std::string> temp;

					str::Parser::Split(str::Parser::Tail(line), temp, " ");

					if (temp.size() != 3u)
					{
						continue;
					}
						
					tempMaterial.Ka.x = std::stof(temp[0]);
					tempMaterial.Ka.y = std::stof(temp[1]);
					tempMaterial.Ka.z = std::stof(temp[2]);
				}
				else if (str::Parser::FirstToken(line) == "Kd")
				{
					// Diffuse Color.

					std::vector<std::string> temp;

					str::Parser::Split(str::Parser::Tail(line), temp, " ");

					if (temp.size() != 3u)
					{
						continue;
					}

					tempMaterial.Kd.x = std::stof(temp[0]);
					tempMaterial.Kd.y = std::stof(temp[1]);
					tempMaterial.Kd.z = std::stof(temp[2]);
				}
				else if (str::Parser::FirstToken(line) == "Ks")
				{
					// Specular Color.

					std::vector<std::string> temp;

					str::Parser::Split(str::Parser::Tail(line), temp, " ");

					if (temp.size() != 3u)
					{
						continue;
					}

					tempMaterial.Ks.x = std::stof(temp[0]);
					tempMaterial.Ks.y = std::stof(temp[1]);
					tempMaterial.Ks.z = std::stof(temp[2]);
				}
				else if (str::Parser::FirstToken(line) == "Ns")
				{
					// Specular exponent.

					tempMaterial.Ns = std::stof(str::Parser::Tail(line));
				}
				else if (str::Parser::FirstToken(line) == "Ni")
				{
					// Optical Dencity.

					tempMaterial.Ni = std::stof(str::Parser::Tail(line));
				}
				else if (str::Parser::FirstToken(line) == "d")
				{
					// Dissolve.

					tempMaterial.d = std::stof(str::Parser::Tail(line));
				}
				else if (str::Parser::FirstToken(line) == "illum")
				{
					// Illunination.

					tempMaterial.illum = std::stoi(str::Parser::Tail(line));
				}				
				else if (str::Parser::FirstToken(line) == "map_Ka")
				{
					// Ambient Texture Map.

					tempMaterial.map_Ka = str::Parser::Tail(line);
				}
				else if (str::Parser::FirstToken(line) == "map_Kd")
				{
					// Diffuse Texture Map.

					tempMaterial.map_Kd = str::Parser::Tail(line);
				}				
				else if (str::Parser::FirstToken(line) == "map_Ks")
				{
					// Specular Texture Map.

					tempMaterial.map_Ks = str::Parser::Tail(line);
				}				
				else if (str::Parser::FirstToken(line) == "map_Ns")
				{
					// Specular Hightlight Map.

					tempMaterial.map_Ns = str::Parser::Tail(line);
				}				
				else if (str::Parser::FirstToken(line) == "map_d")
				{
					// Alpha Texture Map.

					tempMaterial.map_d = str::Parser::Tail(line);
				}				
				else if (str::Parser::FirstToken(line) == "map_Bump" || str::Parser::FirstToken(line) == "map_bump" || str::Parser::FirstToken(line) == "bump")
				{
					// Bump Map.

					tempMaterial.map_bump = str::Parser::Tail(line);
				}
			}

			// Deal with last Material.

			// Push back loaded Material.

			m_LoadedMaterials.push_back(tempMaterial);

			if (m_LoadedMaterials.empty())
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		inFile.close();

		return true;
	}

}