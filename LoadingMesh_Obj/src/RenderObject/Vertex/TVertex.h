#pragma once

//#include "Color.h"

namespace dx9
{
	class TVertex
	{
	public:

	// Constructors:
		
		TVertex();
		TVertex(float _x, float _y, float _z, float _u, float _v);

	// Position:

		float x;
		float y;
		float z;

		float u;
		float v;

	// Flexible vertex format:

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	};
}