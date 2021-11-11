#ifndef LOADER_H
#define LOADER_H

#include "../Components/Mesh.h"

namespace test
{
	class LoaderTest
	{
	public:

	// Constructors and Destructor:

		LoaderTest();

		~LoaderTest();

	// Functions:

		bool LoadObj(const std::string& filePath);

	private:

	// Private Functions:

		std::string FirstToken(std::string& str);

		std::string Tail(const std::string& str);

	// Variables:

		// Loaded Mesh Objects
		std::vector<gfx::Mesh>     LoadedMeshes;
								   
		// Loaded Vertex Objects   
		std::vector<gfx::Vertex>   LoadedVertices;
								   
		// Loaded Index Positions  
		std::vector<uint32>        LoadedIndices;

		// Loaded Material Objects
		std::vector<gfx::Material> LoadedMaterials;
	};
}

#endif // LOADER_H
