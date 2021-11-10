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

	private:

	// Private Functions:

		// Generate vertices from a list of positions, tcoords, normals and a face line.
		void GenerateVerticesFromRawOBJ(std::vector<gfx::Vertex>& oVerts,
			                      const std::vector<gfx::Vector3f>& iPositions,
			                      const std::vector<gfx::Vector2f>& iTCoords,
			                      const std::vector<gfx::Vector3f>& iNormals,
			                            std::string icurline) {};

		// Triangulate a list of vertices into a face by printing inducies corresponding with triangles within it.
		void VertexTriangulation(std::vector<uint32>& oIndices,
			               const std::vector<gfx::Vertex>& iVerts) {};

		// Load Materials from .mtl file
		bool LoadMaterials(std::string path) {};
	};
}

#endif // LOADER_H