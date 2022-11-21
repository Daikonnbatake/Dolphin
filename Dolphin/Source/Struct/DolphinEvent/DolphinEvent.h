#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"

namespace Dolphin
{
    namespace Struct
    {
        template<class... Args> using callback = function<void(Args...)>;


        template<class... Args> struct DolphinEvent
        {
          private:
            unordered_set<callback<Args...>> callbackSet;

          public:
            DolphinEvent();
            void Invoke(Args...);
            void AddEvent(callback<Args...>);
            void PopEvent(callback<Args...>);
        };
    }
}