#pragma once
#include "IButtonReader.h"


namespace Dolphin
{
    namespace StandardComponent
    {
        namespace Input
        {
            struct ButtonStatus : public IButtonReader
            {
              private:
                bool isIdle;
                bool isPush;
                bool isHold;
                bool isPull;

              public:
                void Tick();
                void Push();
                void Pull();
                bool IsIdle() override;
                bool IsPush() override;
                bool IsHold() override;
                bool IsPull() override;
            };
        }
    }
}