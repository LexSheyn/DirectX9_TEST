#include "../../PrecompiledHeaders/stdafx.h"
#include "TriangleShape.h"

namespace dx9
{
// Constructors and Destructor:

	TriangleShape::TriangleShape()
	{
		Verteces[0] = Vertex(  0.0f,  1.0f, 0.0f, Color::Red   );
		Verteces[1] = Vertex(  1.0f, -1.0f, 0.0f, Color::Green );
		Verteces[2] = Vertex( -1.0f, -1.0f, 0.0f, Color::Blue  );
	}
	
	TriangleShape::~TriangleShape()
	{
	}
	

// Function:

	//


// Accessors:

	//
}