#pragma once
#include "DolphinCore.h"
#include "DolphinStd.h"
#include "Source/StandardComponent/Direct2DRenderer/Direct2DRenderer.h"
#include "Source/StandardComponent/Window/Window.h"

#include <d2d1.h>
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
                ID2D1RenderTarget*                  renderTarget;
                IWICImagingFactory*                 factory;
                unordered_map<string, ID2D1Bitmap*> cache;

                template<class T> void SafeRelease(T** ppT)
                { if (*ppT) { (*ppT)->Release(); *ppT = nullptr; } }

              public:
                ImageCache(ID2D1RenderTarget* renderTarget);
                ~ImageCache();
                ID2D1Bitmap* Bitmap(string path);
            };


          private:
            static unordered_map<ID2D1RenderTarget*, ImageCache*>* imageCache;

          private:
            ID2D1RenderTarget*     renderTarget;
            D2D1_RECT_F            spriteRect;
            string                 path;

            void                   Start() override;
            void                   Tick() override;

          public:
            Direct2DSprite(Core::Object* object);
            ~Direct2DSprite();

            void ImagePath(string path);
        };
    }
}