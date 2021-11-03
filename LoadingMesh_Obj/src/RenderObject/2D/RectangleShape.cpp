#include "../../PrecompiledHeaders/stdafx.h"
#include "RectangleShape.h"

namespace dx9
{
// Constructors and Destructor:

	RectangleShape::RectangleShape()
	{
		Vertexes[0] = Vertex( -1.0f,  1.0f, 0.0f, Color::Red    );
		Vertexes[1] = Vertex(  1.0f, -1.0f, 0.0f, Color::Orange );
		Vertexes[2] = Vertex( -1.0f, -1.0f, 0.0f, Color::Yellow );
		Vertexes[3] = Vertex(  1.0f, -1.0f, 0.0f, Color::Green  );
	}
	
	RectangleShape::~RectangleShape()
	{
	}
}