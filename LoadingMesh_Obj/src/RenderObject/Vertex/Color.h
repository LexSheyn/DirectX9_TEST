#pragma once

namespace dx9
{
	class Color
	{
	public:

	// Variables:

		static const D3DCOLOR White  = D3DCOLOR_ARGB(255, 255, 255, 255);
		static const D3DCOLOR Black  = D3DCOLOR_ARGB(255, 000, 000, 000);
		static const D3DCOLOR Red    = D3DCOLOR_ARGB(255, 255, 000, 000);
		static const D3DCOLOR Green  = D3DCOLOR_ARGB(255, 000, 255, 000);
		static const D3DCOLOR Blue   = D3DCOLOR_ARGB(255, 000, 000, 255);
		static const D3DCOLOR Cyan   = D3DCOLOR_ARGB(255, 000, 255, 255);
		static const D3DCOLOR Yellow = D3DCOLOR_ARGB(255, 255, 255, 000);
		static const D3DCOLOR Purple = D3DCOLOR_ARGB(255, 255, 000, 255);
		static const D3DCOLOR Orange = D3DCOLOR_ARGB(255, 255, 155, 000);
		static const D3DCOLOR Pink   = D3DCOLOR_ARGB(255, 255, 100, 255);

		static const D3DCOLOR LightBlue   = D3DCOLOR_ARGB(255, 000, 155, 255);
		static const D3DCOLOR Transparent = D3DCOLOR_ARGB(0, 000, 000, 000);
	};
}