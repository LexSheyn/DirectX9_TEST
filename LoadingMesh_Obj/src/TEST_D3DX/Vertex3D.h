#ifndef VERTEX3D_H
#define VERTEX3D_H

namespace test3d
{
	class Vertex3D
	{
	public:

	// Constructors and Destructor:

		Vertex3D();
		Vertex3D(const float vx, const float vy, const float vz, 
			     const float nx, const float ny, const float nz,
			     const float u,  const float v);

		~Vertex3D();

	// Public Variables:

		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 TextureCoord;
	};
}

#endif // VERTEX3D_H
