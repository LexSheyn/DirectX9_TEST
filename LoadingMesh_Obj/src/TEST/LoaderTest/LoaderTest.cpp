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

				}
			}
		}

		inFile.close();
	}


// Private Functions:

	std::string LoaderTest::FirstToken(std::string& str)
	{
		return std::string();
	}

	std::string LoaderTest::Tail(const std::string& str)
	{
		size_t token_start = str.find_first_not_of(" \t");
		
		size_t space_start = str.find_first_of(" \t", token_start);

		size_t tail_start  = str.find_first_not_of(" \t", space_start);

		size_t tail_end    = str.find_last_not_of(" \t");

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