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
			std::cout << "File format is not .obj" << std::endl;
			
			return false;
		}

		std::ifstream inFile;

		inFile.open(filePath);

		if (inFile.is_open())
		{
			// Clean up before loading into it.
			LoadedMeshes.clear();
			
			LoadedVertices.clear();

			LoadedIndices.clear();

			std::vector<gfx::Vector3f> positions;
			std::vector<gfx::Vector2f> textureCoords;
			std::vector<gfx::Vector3f> normals;

			std::vector<gfx::Vertex> vertices;
			std::vector<uint32>      indices;

			std::vector<std::string> materialNames;

			std::string meshName;

			gfx::Mesh tempMesh;

			std::string line;

			while (std::getline(inFile, line))
			{
				if (line[0] == 'o' || line[0] == 'g')
				{
					meshName = Tail(line);
				}
				else if (line[0] == 'v') // OBJ_Loader.h: 541
				{

				}
			}
		}

		inFile.close();
	}


// Private Functions:

	std::string LoaderTest::FirstToken(std::string& str)
	{
		if (!str.empty())
		{
			uint32 token_start = str.find_first_not_of(" \t");

			uint32 token_end   = str.find_first_of(" \t", token_start);

			if (token_start != std::string::npos && token_end != std::string::npos)
			{
				return str.substr(token_start, token_end - token_start);
			}
			else if (token_start != std::string::npos)
			{
				return str.substr(token_start);
			}
		}

		return "";
	}

	std::string LoaderTest::Tail(const std::string& str)
	{
		uint32 token_start = str.find_first_not_of(" \t");
		
		uint32 space_start = str.find_first_of(" \t", token_start);

		uint32 tail_start  = str.find_first_not_of(" \t", space_start);

		uint32 tail_end    = str.find_last_not_of(" \t");

		if (tail_start != std::string::npos && tail_end != std::string::npos)
		{
			return str.substr(tail_start, tail_end - tail_start + 1u);
		}
		else if (tail_start != std::string::npos)
		{
			return str.substr(tail_start);
		}

		return "";
	}

}