#pragma once
#include "../ButtonStatus/IButtonReader.h"
#include "../CursorState/ICursorStateReader.h"

namespace Dolphin
{
    namespace StandardComponent
    {
        namespace Input
        {
            class IMouseReader
            {
              public:
                virtual ICursorStateReader* Position() = 0;
                virtual IButtonReader*      Left()     = 0;
                virtual IButtonReader*      Middle()   = 0;
                virtual IButtonReader*      Right()    = 0;
            };
        }
    }
}