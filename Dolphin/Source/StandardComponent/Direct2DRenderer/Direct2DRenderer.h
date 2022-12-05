#pragma once
#pragma comment(lib, "d3d11.lib")
#include "DolphinCore.h"
#include "DolphinStd.h"
#include "Source/StandardComponent/Window/Window.h"

#include <d2d1_1.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <windows.h>


namespace Dolphin
{
    namespace StandardComponent
    {
        class Direct2DRenderer : public Dolphin::Core::Component
        {
          private:
            HWND                   windowHandle;
            ID3D11Device*          d3dDevice;
            IDXGIDevice1*          dxgiDevice;
            ID2D1Factory1*         d2dFactory;
            ID2D1Device*           d2dDevice;
            ID2D1DeviceContext*    d2dDeviceContext;
            IDXGIAdapter*          dxgiAdapter;
            IDXGIFactory2*         dxgiFactory;
            IDXGISwapChain1*       dxgiSwapChain;
            IDXGISurface*          dxgiSurface;
            ID2D1Bitmap1*          backBuffer;

            void                   Start() override;
            void                   Tick() override;
            void                   LateTick() override;

          public:
            Direct2DRenderer(Dolphin::Core::Object* object);
            ~Direct2DRenderer();
            ID2D1DeviceContext* DeviceContext();
            template<class Interface> void SafeRelease(Interface** target);
        };
    }
}