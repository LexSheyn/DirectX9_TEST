#include "../PrecompiledHeaders/stdafx.h"
#include "LightSource.h"
#include "d3d9types.h"

namespace dx9
{
// Constructors and Destructor:

	LightSource::LightSource()
	{
		m_Color = Color::White;

		m_Light.Type      = D3DLIGHT_DIRECTIONAL;
		m_Light.Position  = D3DXVECTOR3(  2.0f, 0.0f, 5.0f );
		m_Light.Direction = D3DXVECTOR3( -1.0f, 0.0f, 0.0f );
		
		// Color.
		m_Light.Ambient  = m_Color * 0.4f;
		m_Light.Diffuse  = m_Color;
		m_Light.Specular = m_Color * 0.6f;
	}

	LightSource::~LightSource()
	{
	}


// Functions:

	//


// Accessors:

	const D3DLIGHT9* LightSource::GetD3DLight() const
	{
		return &m_Light;
	}


// Modifiers:

	//

}