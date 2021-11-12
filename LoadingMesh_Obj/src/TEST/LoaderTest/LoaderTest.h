#ifndef LOADER_H
#define LOADER_H

#include "Parser.h"

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

		// Generate vertices from a list of positions, tcoords, normals and a face line.
		void GenerateVerticesFromRawObj(std::vector<gfx::Vertex>& oVertices,
			                      const std::vector<gfx::Vector3f>& iPositions,
			                      const std::vector<gfx::Vector2f>& iTextureCoords,
			                      const std::vector<gfx::Vector3f>& iNormals,
			                      const std::string& iLine);

		// Triangulate a list of vertices into a face by printing, inducies corresponding with triangles within it.
		void VertexTriangulation(std::vector<uint32>& oIndices,
			               const std::vector<gfx::Vertex>& iVertices);

		// Load Materials from .mtl file.
		bool LoadMaterials(const std::string& filePath);

	// Variables:

		// Loaded Mesh Objects
		std::vector<gfx::Mesh>     m_LoadedMeshes;
								   
		// Loaded Vertex Objects   
		std::vector<gfx::Vertex>   m_LoadedVertices;
								   
		// Loaded Index Positions  
		std::vector<uint32>        m_LoadedIndices;

		// Loaded Material Objects
		std::vector<gfx::Material> m_LoadedMaterials;
	};
}

#endif // LOADER_H
