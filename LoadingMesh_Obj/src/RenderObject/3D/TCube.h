#ifndef TCUBE_H
#define TCUBE_H

#include "../Transformable.h"

namespace dx9
{
	class TCube : public Transformable
	{
	public:

	// Constructors and Destructors:

		TCube();

		~TCube();

	// Functions:

		//

	// Accessors:

		const std::string& GetTexturePath() const;

	// Modifiers:
		
		void SetPosition(D3DXVECTOR3 position);
		void SetPosition(float x, float y, float z);

		void SetRotation(D3DXVECTOR3 rotation);
		void SetRotation(float x, float y, float z);

		void SetScale(D3DXVECTOR3 scale);
		void SetScale(float x, float y, float z);

		void SetTexture(IDirect3DDevice9* device, LPCWSTR filePath);

	// Temporary Public Variables:

		static const uint32 VerticesNumber = 24;

		TVertex Vertices[VerticesNumber];

		static const uint32 IndicesNumber = 36;

		// Possibly should be 'const'
		int32 Indices[IndicesNumber] =
		{
			// Front face.
			0, 1, 2,
			2, 1, 3,

			// Back face.
			4, 5, 6,
			6, 5, 7,

			// Left face.
			8, 9, 10,
			10, 9, 11,

			// Right face.
			12, 13, 14,
			14, 13, 15,

			// Top face.
			16, 17, 18,
			18, 17, 19,

			// Bottom face.
			20, 21, 22,
			22, 21, 23
		};

	private:

	// Variables:

		D3DXVECTOR3 m_Position;
		D3DXVECTOR3 m_Rotation;
		D3DXVECTOR3 m_Scale;

		IDirect3DTexture9* m_Texture;
		std::string m_TexturePath;
	};
}
#endif // TCUBE_H