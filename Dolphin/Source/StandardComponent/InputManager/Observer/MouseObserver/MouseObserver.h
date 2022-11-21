#pragma once
#include "../ButtonStatus/ButtonStatus.h"
#include "../ButtonStatus/IButtonReader.h"
#include "../CursorState/CursorState.h"
#include "../CursorState/ICursorStateReader.h"
#include "IMouseReader.h"
#include "DolphinMacro.h"

#include <windows.h>
#include <winuser.h>

namespace Dolphin
{
    namespace StandardComponent
    {
        namespace Input
        {
            typedef int keyCode;

            class MouseObserver : public IMouseReader
            {
              private:
                static MouseObserver* instance;
                CursorState           position;
                ButtonStatus          left;
                ButtonStatus          middle;
                ButtonStatus          right;

                MouseObserver();
                ~MouseObserver();
                void UpdateButton(keyCode keyCode, ButtonStatus& target);

              public:
                void                  Tick();
                ICursorStateReader*   Position() override;
                IButtonReader*        Left() override;
                IButtonReader*        Middle() override;
                IButtonReader*        Right() override;


                static MouseObserver* Initialize();
                static MouseObserver* Instance();
                static void           Destroy();
            };
        }
    }
}