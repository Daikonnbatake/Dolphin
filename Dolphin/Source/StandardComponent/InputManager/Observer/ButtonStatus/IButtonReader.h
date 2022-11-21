#pragma once

namespace Dolphin
{
    namespace StandardComponent
    {
        namespace Input
        {
            class IButtonReader
            {
              public:
                virtual bool IsIdle() = 0;
                virtual bool IsPush() = 0;
                virtual bool IsHold() = 0;
                virtual bool IsPull() = 0;
            };
        }
    }
}