#pragma once
#include "DolphinCore.h"
#include "Source/StandardComponent/Direct2DRenderer/Direct2DRenderer.h"
#include "Source/StandardComponent/Window/Window.h"
#include <windows.h>
#include <d2d1.h>
#include <wincodec.h>

namespace Dolphin
{
    namespace StandardComponent
    {
        class Direct2DSprite : public Core::Component
        {
        private:
            ID2D1RenderTarget* renderTarget;
            IWICImagingFactory* factory;
            IWICBitmapDecoder* decoder;
            IWICBitmapFrameDecode* frame;
            IWICFormatConverter* formatConverter;
            ID2D1Bitmap* bitmap;
            HWND windowHandle;

            void Start() override;
            void Tick() override;

        public:
            Direct2DSprite(Core::Object* object);
            ~Direct2DSprite();
        };
    }
}