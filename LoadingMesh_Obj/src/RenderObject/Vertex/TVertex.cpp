#include "../../PrecompiledHeaders/stdafx.h"
#include "TVertex.h"

namespace dx9
{
// Constructors:

	TVertex::TVertex()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;

		u = 0.0f;
		v = 0.0f;
	}

	TVertex::TVertex(float _x, float _y, float _z, float _u, float _v)
	{
		x = _x;
		y = _y;
		z = _z;

		u = _u;
		v = _v;
	}
}
