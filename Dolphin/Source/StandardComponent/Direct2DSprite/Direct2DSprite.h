#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxguid.lib")
#include "DolphinCore.h"
#include "DolphinStd.h"
#include "DolphinStruct.h"
#include "Source/StandardComponent/Direct2DRenderer/Direct2DRenderer.h"
#include "Source/StandardComponent/Window/Window.h"
#include "AffineBuilder.h"

//#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <wincodec.h>
#include <windows.h>

namespace Dolphin
{
    namespace StandardComponent
    {
        class Direct2DSprite : public Core::Component
        {
          private:

            struct ImageCache
            {
              private:
                ID2D1DeviceContext*                  deviceContext;
                IWICImagingFactory*                  factory;
                unordered_map<string, ID2D1Bitmap1*> cache;

                template<class T> void SafeRelease(T** ppT)
                { if (*ppT) { (*ppT)->Release(); *ppT = nullptr; } }

              public:
                ImageCache(ID2D1DeviceContext* deviceContext);
                ~ImageCache();
                ID2D1Bitmap1* Bitmap(string path);
            };


          private:
            static unordered_map<ID2D1RenderTarget*, ImageCache*>* imageCache;

          private:
            ID2D1DeviceContext*    deviceContext;
            D2D1_RECT_F            spriteRect;
            D2D1_RECT_F            clippingRect;
            D2D1_MATRIX_3X2_F      matrix;
            string                 path;
            ID2D1Bitmap1*          bitmap;

            void                   Start() override;
            void                   Tick() override;

          public:
            Direct2DSprite(Core::Object* object);
            ~Direct2DSprite();

            void ImagePath(string path);
            D2D1_RECT_F CropRect();
            void AffineTransform(AffineBuilder affineBuilder);
            void Clipping(float left, float top, float right, float bottom);
            void ClearClipping();
        };
    }
}