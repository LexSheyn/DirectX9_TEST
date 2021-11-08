#include "../../PrecompiledHeaders/stdafx.h"
#include "RectangleShape.h"

namespace dx9
{
// Constructors and Destructor:

	RectangleShape::RectangleShape()
	{
		Vertices[0] = SVertex( -1.0f,  1.0f, 0.0f, Color::Green  );
		Vertices[1] = SVertex(  1.0f,  1.0f, 0.0f, Color::Blue   );
		Vertices[2] = SVertex( -1.0f, -1.0f, 0.0f, Color::Red    );
		Vertices[3] = SVertex(  1.0f, -1.0f, 0.0f, Color::Purple );
	}
	
	RectangleShape::~RectangleShape()
	{
	}
	

// Accessors:

	//
}