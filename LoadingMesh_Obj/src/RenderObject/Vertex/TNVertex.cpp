#include "../../PrecompiledHeaders/stdafx.h"
#include "TNVertex.h"

namespace dx9
{
// Constructors and Destructor:

	TNVertex::TNVertex()
	{
	// Positions:

		x = 0.0f;
		y = 0.0f;
		z = 0.0f;

	// Normals:

		nx = 0.0f;
		ny = 0.0f;
		nz = 0.0f;

	// Texture coordinates:

		u = 0.0f;
		v = 0.0f;
	}

	TNVertex::TNVertex(float32 _x, float32 _y, float32 _z, float32 _nx, float32 _ny, float32 _nz, float32 _u, float32 _v)
	{
	// Positions:

		x = _x;
		y = _y;
		z = _z;

	// Normals:

		nx = _nx;
		ny = _ny;
		nz = _nz;

	// Texture coordinates:

		u = _u;
		v = _v;
	}

	TNVertex::~TNVertex()
	{
	}

}