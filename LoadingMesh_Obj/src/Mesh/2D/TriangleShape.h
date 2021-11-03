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

	// Public Variables:

		static const uint32 VertexNumber = 3;

//	private:

	// Variables:

		Vertex Vertexes[VertexNumber];
	};
}