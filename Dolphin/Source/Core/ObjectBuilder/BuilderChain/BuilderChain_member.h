#pragma once
#include "Source/Core/Object/Object_forward.h"
#include "Source/StandardComponent/Nest/Nest.h"
#include "BuilderChain_forward.h"

namespace Dolphin
{
	class BuilderChain
	{
	private:
		Dolphin::Core::Object* object;
		Dolphin::StandardComponent::Nest* nest;

	public:
		BuilderChain(Dolphin::Core::Object* object);

		operator Dolphin::Core::Object* ();

		template<class T> BuilderChain& AddComponent();
		BuilderChain& Child(BuilderChain& obj);
	};
}