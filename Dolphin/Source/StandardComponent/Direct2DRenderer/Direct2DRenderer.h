#pragma once
#pragma comment(lib, "d2d1")
#include "DolphinCore.h"
#include "DolphinStd.h"
#include "Source/StandardComponent/Window/Window.h"

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <windows.h>


namespace Dolphin
{
    namespace StandardComponent
    {
        class Direct2DRenderer : public Dolphin::Core::Component
        {
          private:
            HWND                   windowHandle;
            ID2D1Factory*          direct2DFactory;
            ID2D1HwndRenderTarget* renderTarget;
            function<void(void)>   rendering;

            void                   Start() override;

          public:
            Direct2DRenderer(Dolphin::Core::Object* object);
            ~Direct2DRenderer();
            ID2D1HwndRenderTarget* Rendertarget();
            void RenderingProcess(function<void(void)> renderingProcess);
            template<class Interface> void SafeRelease(Interface** target);
        };
    }
}