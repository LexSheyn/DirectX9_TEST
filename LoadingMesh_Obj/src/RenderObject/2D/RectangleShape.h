#pragma once

#include "Shape.h"

namespace dx9
{
	class RectangleShape : public Shape
	{
	public:

	// Constructors and Destructor:

		RectangleShape();

		~RectangleShape();

	// Functions:

		//

	// Accessors:

		//

	// Temporary Public Variables:

		static const uint32 VerticesNumber = 4;

		Vertex Vertices[VerticesNumber];

		static const uint32 IndicesNumber = 6;

		// Possibly should be 'const'
		int32 Indices[IndicesNumber] =
		{
			0, 1, 2,
			2, 1, 3
		};
	};
}