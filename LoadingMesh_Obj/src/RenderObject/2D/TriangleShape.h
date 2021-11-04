#pragma once

#include "Shape.h"

namespace dx9
{
	class TriangleShape : public Shape
	{
	public:

	// Constructors and Destructor:

		TriangleShape();

		~TriangleShape();

	// Function:

		//

	// Accessors:

		//

	// Temporary Public Variables:

		static const uint32 VerticesNumber = 3;

		Vertex Vertices[VerticesNumber];

		static const uint32 IndicesNumber = 3;

		// Possibly should be 'const'
		int32 Indices[IndicesNumber] =
		{
			0, 1, 2
		};
	};
}