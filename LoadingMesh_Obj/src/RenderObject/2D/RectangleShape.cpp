#include "../../PrecompiledHeaders/stdafx.h"
#include "RectangleShape.h"

namespace dx9
{
// Constructors and Destructor:

	RectangleShape::RectangleShape()
	{
		Vertices[0] = Vertex( -1.0f,  1.0f, 0.0f, Color::Red    );
		Vertices[1] = Vertex(  1.0f,  1.0f, 0.0f, Color::Orange );
		Vertices[2] = Vertex( -1.0f, -1.0f, 0.0f, Color::Yellow );
		Vertices[3] = Vertex(  1.0f, -1.0f, 0.0f, Color::Green  );
	}
	
	RectangleShape::~RectangleShape()
	{
	}
	

// Accessors:

	//
}