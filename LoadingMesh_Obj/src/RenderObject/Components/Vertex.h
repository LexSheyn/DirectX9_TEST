#ifndef VERTEX_H
#define VERTEX_H

#include "VectorMath.h"

namespace gfx
{
	class Vertex
	{
	public:

	// Variables:

		Vector3f Position;

		Vector3f Normal;

		Vector2f TextureCoordinate;
	};
}

#endif // MESH_H
