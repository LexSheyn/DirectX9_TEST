#pragma once

#include "../RenderSystem/RenderSystem.h"

namespace dx9
{
	class Updater
	{
	public:

	// Constructors and Destructors:

		Updater();

		~Updater();

	// Functions:

		void SetRenderSystem(RenderSystem* renderSystem);

		void Update(const float& dt);

	private:

	// Variables:

		// TEST
		RenderSystem* m_RenderSystemPtr;
	};
}
