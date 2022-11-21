#pragma once
#include "Core/Component.h"
#include "DolphinStd.h"
#include "Observer/KeyCode.h"
#include "Observer/KeyboardObserver/IKeyboardReader.h"
#include "Observer/KeyboardObserver/KeyboardObserver.h"
#include "Observer/MouseObserver/IMouseReader.h"
#include "Observer/MouseObserver/MouseObserver.h"

namespace Dolphin
{
    namespace StandardComponent
    {
        class InputManager : public Core::Component
        {
          private:
            Input::KeyboardObserver* keyboardObserver;
            Input::MouseObserver*    mouseObserver;


          public:
            InputManager(Core::Object* object);
            ~InputManager();

            void                    Tick() override;
            Input::IMouseReader*    MouseStatus();
            Input::IKeyboardReader* KeyboardStatus();
        };
    }
}