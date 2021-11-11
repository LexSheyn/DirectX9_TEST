#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "Material.h"

namespace gfx
{
	class Mesh
	{
	public:

	// Constructors:

		Mesh();
		Mesh(std::vector<Vertex>& _vertices, std::vector<uint32>& _indices);

	// Variables:

		// Mesh Name
		std::string MeshName;

		// Vertex List
		std::vector<Vertex> Vertices;

		// Index List
		std::vector<uint32> Indices;

		// Material
		Material MeshMaterial;
	};
}

#endif // MESH_H