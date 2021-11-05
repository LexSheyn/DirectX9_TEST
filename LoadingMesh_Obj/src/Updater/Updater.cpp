#include "../PrecompiledHeaders/stdafx.h"
#include "Updater.h"

namespace dx9
{
// Constructors and Destructor:

	Updater::Updater()
	{
		m_RenderSystemPtr = nullptr;
	}
	
	Updater::~Updater()
	{
	}
	

// Functions:

	void Updater::SetRenderSystem(RenderSystem* renderSystem)
	{
		m_RenderSystemPtr = renderSystem;
	}

	void Updater::Update(const float& dt)
	{
		m_RenderSystemPtr->GetCamera().Update(dt);
	}
}