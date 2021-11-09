#include "../../PrecompiledHeaders/stdafx.h"
#include "Mesh.h"

namespace dx9
{
// Constructors:

	Mesh::Mesh()
	{
	}

	Mesh::Mesh(std::vector<Vertex>& _vertices, std::vector<uint32>& _indices)
	{
		Vertices = _vertices;

		Indices  = _indices;
	}

}