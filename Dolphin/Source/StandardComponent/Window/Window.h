#pragma once
#include "DolphinCore.h"
#include "DolphinStd.h"
#include "DolphinStruct.h"

#include <windows.h>


namespace Dolphin
{
    namespace StandardComponent
    {
        class Window : public Dolphin::Core::Component
        {
          private:
            HWND                                          parentHandle;
            bool                                          closed;
            long                                          windowStyle;
            HWND                                          windowHandle;
            HINSTANCE                                     instanceHandle;
            WNDCLASS                                      windowClass;
            string                                        className;
            string                                        windowName;
            Struct::Vector2                               position;
            Struct::Vector2                               size;
            function<LRESULT(HWND, UINT, WPARAM, LPARAM)> thirdWindowProcedure;


            void                                          Quit();
            void             GenerateWindowClass(WNDCLASS& target);
            LRESULT CALLBACK WindowProcedure(
                HWND   windowHandle,
                UINT   message,
                WPARAM wordParam,
                LPARAM longParam);
            static LRESULT CALLBACK StaticWindowProc(
                HWND   windowHandle,
                UINT   message,
                WPARAM wordParam,
                LPARAM longParam);

          public:
            Window(Dolphin::Core::Object* object);
            bool             Closed();
            HWND             WindowHandle();
            void             Position(Struct::Vector2& position);
            Struct::Vector2  Position();
            void             Size(Struct::Vector2& size);
            Struct::Vector2  Size();
            string           Title();
            void             Title(string title);
            void             Style(long windowStyle);
            void             ThirdWindowProcedure(function<LRESULT(HWND, UINT, WPARAM, LPARAM)> windowProc);
        };
    }
}