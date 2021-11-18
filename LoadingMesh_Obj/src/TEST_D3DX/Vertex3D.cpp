#include "../PrecompiledHeaders/stdafx.h"
#include "Vertex3D.h"

namespace test3d
{
// Constructors and Destructor:

	Vertex3D::Vertex3D()
	{
	}

	Vertex3D::Vertex3D(const float vx, const float vy, const float vz, 
		               const float nx, const float ny, const float nz, 
		               const float u,  const float v)
	{
		Position.x = vx;
		Position.y = vy;
		Position.z = vz;

		Normal.x = nx;
		Normal.y = ny;
		Normal.z = nz;

		TextureCoord.x = u;
		TextureCoord.y = v;
	}

	Vertex3D::~Vertex3D()
	{
	}

}