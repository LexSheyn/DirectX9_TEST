#pragma once

namespace dx9
{
	class MVertex
	{
	public:

		// Constructors and Destructor:

		MVertex();

		~MVertex();

		// Functions:

			//

	private:

		// Variables:

		D3DXVECTOR3 Vertices;
		D3DXVECTOR3 Normals;

		float TextureU;
		float TextureV;

		static const ULONG FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	};
}
