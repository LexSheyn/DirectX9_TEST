#include "../PrecompiledHeaders/stdafx.h"
#include "Vertex.h"

namespace dx9
{
// Constructors:

	Vertex::Vertex()
	{
		x     = 0.0f;
		y     = 0.0f;
		z     = 0.0f;
		color = Color::Red;
	}

	Vertex::Vertex(const float _x, const float _y, const float _z, D3DCOLOR _color)
	{
		x     = _x;
		y     = _y;
		z     = _z;
		color = _color;
	}
}
