#include "../../PrecompiledHeaders/stdafx.h"
#include "Material.h"

namespace gfx
{
// Constructor:

	Material::Material()
	{
		Ns    = 0.0f;
		Ni    = 0.0f;
		d     = 0.0f;
		illum = 0;
	}

}