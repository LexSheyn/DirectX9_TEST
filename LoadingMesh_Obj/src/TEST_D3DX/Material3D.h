#ifndef MATERIAL3D_H
#define MATERIAL3D_H

namespace test3d
{
	class Material3D
	{
	public:

	// Constructors and Destructor:

		Material3D();

		~Material3D();

	// Public Variables:

		char8 strName[MAX_PATH];

		D3DXVECTOR3 vAmbient;
		D3DXVECTOR3 vDiffuse;
		D3DXVECTOR3 vSpecular;

		int32 nShininess;
		float32 fAlpha;

		bool bSpecular;

		char8 strTexture[MAX_PATH];

		IDirect3DTexture9* pTexture;

		D3DXHANDLE hTechnique;
	};
}

#endif // MATERIAL3D_H
