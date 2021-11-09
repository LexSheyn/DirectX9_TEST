#include "../../PrecompiledHeaders/stdafx.h"
#include "SVertex.h"

namespace dx9
{
// Constructors:

	SVertex::SVertex()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;

		color = Color::Red;
	}

	SVertex::SVertex(float _x, float _y, float _z, D3DCOLOR _color)
	{
		x = _x;
		y = _y;
		z = _z;

		color = _color;
	}
}
