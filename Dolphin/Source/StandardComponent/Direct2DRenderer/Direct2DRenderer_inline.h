#pragma once
#include "Direct2DRenderer.h"


template<class Interface>
inline void Dolphin::StandardComponent::Direct2DRenderer::SafeRelease(Interface** target)
{
	if (target != NULL)
	{
		(*target)->Release();
		(*target) = NULL;
	}
}