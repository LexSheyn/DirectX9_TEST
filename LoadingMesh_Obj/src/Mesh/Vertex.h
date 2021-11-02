#pragma once

#include "Color.h"

namespace dx9
{
	class Vertex
	{
	public:

	// Constructors:
		
		Vertex();
		Vertex(const float _x, const float _y, const float _z, D3DCOLOR _color);

	// Position:

		float x;
		float y;
		float z;

	// Color:

		D3DCOLOR color;

	// Flexible vertex format:

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	};
}