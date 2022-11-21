#pragma once
#include "../ButtonStatus/IButtonReader.h"


namespace Dolphin
{
    namespace StandardComponent
    {
        namespace Input
        {
            class IKeyboardReader
            {
            public:
                virtual IButtonReader* KeyState(int virtualKeyCode) = 0;
            };
        }
    }
}