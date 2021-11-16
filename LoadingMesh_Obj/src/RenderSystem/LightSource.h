#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "../RenderObject/Color.h"

namespace dx9
{
	class LightSource
	{
	public:

	// Constructors and Destructor:

		LightSource();

		~LightSource();

	// Functions:

		//

	// Accessors:

		const D3DLIGHT9* GetD3DLight() const;

	// Modifiers:

		//

	private:

	// Variables:

		D3DXCOLOR m_Color;

		D3DLIGHT9 m_Light;		
	};
}

#endif // LIGHTSOURCE_H