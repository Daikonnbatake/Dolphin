#pragma once
#include "BuilderChain/BuilderChain.h"
#include "DolphinStd.h"
#include "ObjectBuilder_forward.h"
#include "Source/Core/Object/Object_member.h"
#define NEW(name) Dolphin::ObjectBuilder::Instantiate(name)


namespace Dolphin
{
    class ObjectBuilder
    {
      public:
        static BuilderChain Instantiate(string name);
    };
}