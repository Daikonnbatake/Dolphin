#pragma once

namespace Dolphin
{
    namespace StandardComponent
    {
        namespace Input
        {
            class ICursorStateReader
            {
              public:
                virtual int X() = 0;
                virtual int Y() = 0;
            };
        }
    }
}