#pragma once

#include "GraphicDevice.h"

namespace dx9
{
	class Renderer
	{
	public:

	// Constructors and Destructor:

		Renderer();

		~Renderer();

	// Functions:

		void Render();

	// Accessors:

		GraphicDevice* getDevice() const;

	private:

	// Variables:

		GraphicDevice* m_Device;
	};
}
