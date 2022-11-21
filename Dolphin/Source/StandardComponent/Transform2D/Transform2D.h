#pragma once
#include "Core/Component.h"
#include "DolphinStruct.h"

namespace Dolphin
{
    namespace StandardComponent
    {
        class Transform2D : public Dolphin::Core::Component
        {
          private:
            Dolphin::Struct::Vector2 position;
            Dolphin::Struct::Vector2 scale;
            Dolphin::Struct::Angle   rotate;

          public:
            Transform2D(Dolphin::Core::Object* object);
            Dolphin::Struct::Vector2& Position();
            Dolphin::Struct::Vector2& Scale();
            Dolphin::Struct::Angle&   Rotate();
            void Position(Dolphin::Struct::Vector2& position);
            void Scale(Dolphin::Struct::Vector2& scale);
            void Rotate(Dolphin::Struct::Angle& rotate);
        };
    }
}