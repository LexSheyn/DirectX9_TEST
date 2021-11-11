#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector3f.h"

namespace gfx
{
	class Material
	{
	public:

	// Constructor:

		Material();

	// Variables:

		// Material Name
		std::string Name;

		// Ambient Color: Ka
		Vector3f Ka;

		// Diffuse Color: Kd
		Vector3f Kd;

		// Specular Color: Ks
		Vector3f Ks;

		// Specular Exponent: Ns
		float Ns;

		// Optical Dencity: Ni
		float Ni;

		// Dissolve: d
		float d;

		// Illumination: illum
		int32 illum;

		// Ambient Texture Map: map_Ka
		std::string map_Ka;

		// Diffuse Texture Map: map_Kd
		std::string map_Kd;

		// Specular Texture Map: map_Ks
		std::string map_Ks;

		// Specular Highlight Map: map_Ns
		std::string map_Ns;

		// Alpha Texture Map: map_d
		std::string map_d;			

		// Bump Map: map_Bump
		std::string map_bump;
	};
}

#endif // MATERIAL_H