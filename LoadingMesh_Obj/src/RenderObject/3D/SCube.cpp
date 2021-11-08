#include "../../PrecompiledHeaders/stdafx.h"
#include "SCube.h"

namespace dx9
{
// Constructors and Destructor:

	SCube::SCube()
	{
		// Front.
		Vertices[0] = SVertex( -1.0f,  1.0f, -1.0f, Color::Green  );
		Vertices[1] = SVertex(  1.0f,  1.0f, -1.0f, Color::Blue   );
		Vertices[2] = SVertex( -1.0f, -1.0f, -1.0f, Color::Red    );
		Vertices[3] = SVertex(  1.0f, -1.0f, -1.0f, Color::Purple );

		// Back.
		Vertices[4] = SVertex( -1.0f,  1.0f, 1.0f, Color::LightBlue );
		Vertices[5] = SVertex(  1.0f,  1.0f, 1.0f, Color::Pink      );
		Vertices[6] = SVertex( -1.0f, -1.0f, 1.0f, Color::Orange    );
		Vertices[7] = SVertex(  1.0f, -1.0f, 1.0f, Color::Yellow    );
	}

	SCube::~SCube()
	{
	}

}