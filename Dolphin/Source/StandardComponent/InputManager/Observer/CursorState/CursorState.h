#pragma once
#include "ICursorStateReader.h"

namespace Dolphin
{
    namespace StandardComponent
    {
        namespace Input
        {
            struct CursorState : public ICursorStateReader
            {
              private:
                int x;
                int y;


              public:
                CursorState();
                ~CursorState();

                void X(int x);
                void Y(int y);
                int X() override;
                int Y() override;
            };
        }
    }
}