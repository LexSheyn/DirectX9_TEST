#ifndef LOADER_H
#define LOADER_H

#include "Tools.h"

#include "../RenderObject/Components/Mesh.h"
#include "../RenderObject/Components/Vertex.h"
#include "../RenderObject/Components/Material.h"

namespace tool
{
	class Loader
	{
	public:

	// Constructors and Destructor:

		Loader();

		~Loader();

	// Functions:

		// Load a file into the loader.
		// If file is loaded return true.
		// If the file is unable to be found or unable to be loaded return false.
		bool LoadObj(const std::string& filePath);

	// Public Variables:

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