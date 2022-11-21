#pragma once
#include "BuilderChain_forward.h"
#include "Source/Core/Object/Object_forward.h"
#include "Source/StandardComponent/Nest/Nest.h"

namespace Dolphin
{
    class BuilderChain
    {
      private:
        Dolphin::Core::Object*            object;
        Dolphin::StandardComponent::Nest* nest;

      public:
        BuilderChain(Dolphin::Core::Object* object);

                                        operator Dolphin::Core::Object*();

        template<class T> BuilderChain& AddComponent();
        BuilderChain&                   Child(BuilderChain& obj);
    };
}