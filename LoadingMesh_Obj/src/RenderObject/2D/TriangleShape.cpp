#include "../../PrecompiledHeaders/stdafx.h"
#include "TriangleShape.h"

namespace dx9
{
// Constructors and Destructor:

	TriangleShape::TriangleShape()
	{
		Vertices[0] = SVertex(  0.0f,  1.0f, 0.0f, Color::Red   );
		Vertices[1] = SVertex(  1.0f, -1.0f, 0.0f, Color::Green );
		Vertices[2] = SVertex( -1.0f, -1.0f, 0.0f, Color::Blue  );
	}
	
	TriangleShape::~TriangleShape()
	{
	}
	

// Function:

	//


// Accessors:

	//
}