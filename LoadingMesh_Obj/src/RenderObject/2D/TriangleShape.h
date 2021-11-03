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

		static const uint32 VertecesNumber = 3;

		Vertex Verteces[VertecesNumber];
	};
}