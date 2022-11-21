#pragma once
#include "../ButtonStatus/ButtonStatus.h"
#include "../ButtonStatus/IButtonReader.h"
#include "IKeyboardReader.h"
#include "DolphinStd.h"

#include <windows.h>
#include <winuser.h>


namespace Dolphin
{
    namespace StandardComponent
    {
        namespace Input
        {
            typedef int keyCode;

            class KeyboardObserver : public IKeyboardReader
            {
              private:
                static KeyboardObserver*         instance;
                unordered_map<int, ButtonStatus> key;

                KeyboardObserver();
                ~KeyboardObserver();
                void UpdateButton(keyCode keyCode, ButtonStatus& target);


              public:
                void                     Tick();
                IButtonReader*           KeyState(keyCode virtualKeyCode);

                static KeyboardObserver* Initialize();
                static KeyboardObserver* Instance();
                static void              Destroy();
            };
        }
    }
}