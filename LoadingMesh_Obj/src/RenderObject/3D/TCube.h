#ifndef TCUBE_H
#define TCUBE_H

#pragma once

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

		void SetTexture(const char* filePath);

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
			5, 4, 7,
			7, 4, 6,

			// Right face.
			1, 5, 3,
			3, 5, 7,

			// Left face.
			4, 0, 6,
			6, 0, 2,

			// Top face.
			4, 5, 0,
			0, 5, 1,

			// Bottom face.
			2, 3, 6,
			6, 3, 7
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