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

		Vector2f TextureCoord;

		// TEST
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	};
}

#endif // MESH_H
