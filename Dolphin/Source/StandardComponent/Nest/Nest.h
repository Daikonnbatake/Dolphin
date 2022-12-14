#pragma once
#include "DolphinCore.h"
#include "DolphinMacro.h"
#include "DolphinStd.h"


namespace Dolphin
{
    namespace StandardComponent
    {
        class Nest : public Dolphin::Core::Component
        {
          private:
            Dolphin::Core::Object*         parent;
            vector<Dolphin::Core::Object*> children;
            void                   Tick() override;


          public:
            Nest(Dolphin::Core::Object* object);
            ~Nest() override;
            int           ChildCount();
            Core::Object* Parent();
            Core::Object* MoveTo(Core::Object* target);
            Core::Object* AddChild(string name);
            Core::Object* GetChild(string name);
        };
    }
}