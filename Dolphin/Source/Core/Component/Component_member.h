#pragma once
#include "Component_forward.h"
#include "Source/Core/Object/Object_member.h"


namespace Dolphin
{
    namespace Core
    {
        class Component
        {
            friend class Object;


          protected:
            Object* object;

            Component(Object* object);
            virtual ~Component() {};
            virtual void Start() {};
            virtual void Tick() {};


          public:
            Object* ThisObject();
        };
    }
}