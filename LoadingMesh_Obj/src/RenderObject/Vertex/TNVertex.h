#ifndef TNVERTEX_H
#define TNVERTEX_H

namespace dx9
{
	class TNVertex
	{
	public:

	// Constructors and Destructor:

		TNVertex();
		TNVertex(float32 _x, float32 _y, float32 _z, float32 _nx, float32 _ny, float32 _nz, float32 _u, float32 _v);

		~TNVertex();

	// Position:

		float32 x;
		float32 y;
		float32 z;

	// Normals:

		float32 nx;
		float32 ny;
		float32 nz;

	// Texture coordinates:

		float32 u;
		float32 v;

	// Flexible Vertex Format:

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
	};
}

#endif // TNVERTEX_H
