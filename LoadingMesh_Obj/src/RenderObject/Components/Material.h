#pragma once

#include "Vector3f.h"

namespace dx9
{
	class Material
	{
	public:

	// Constructor:

		Material();

	// Variables:

		// Material Name
		std::string Name;

		// Ambient Color
		Vector3f ColorAmbient;

		// Diffuse Color
		Vector3f ColorDiffuse;

		// Specular Color
		Vector3f ColorSpecular;

		// Specular Exponent
		float NSpecular;

		// Optical Dencity
		float NDencity;

		// Dissolve
		float Dissolve;

		// Illumination
		int32 Illumination;

		// Ambient Texture Map
		std::string MapTextureAmbient;

		// Diffuse Texture Map
		std::string MapTextureDiffuse;

		// Specular Texture Map
		std::string MapTextureSpecular;

		// Alpha Texture Map
		std::string MapTextureAlpha;

		// Specular Highlight Map
		std::string MapHighlightSpecular;		

		// Bump Map
		std::string MapBump;
	};
}
