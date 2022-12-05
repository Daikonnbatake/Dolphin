#include "pch.h"
#include "Direct2DRenderer.h"

#include "Direct2DRenderer_inline.h"


Dolphin::StandardComponent::Direct2DRenderer::Direct2DRenderer(
    Dolphin::Core::Object* object)
    : Component(object)
{
    this->windowHandle     = nullptr;
    this->d3dDevice        = nullptr;
    this->dxgiDevice       = nullptr;
    this->d2dFactory       = nullptr;
    this->d2dDevice        = nullptr;
    this->d2dDeviceContext = nullptr;
    this->dxgiAdapter      = nullptr;
    this->dxgiFactory      = nullptr;
    this->dxgiSwapChain    = nullptr;
    this->dxgiSurface      = nullptr;
    this->backBuffer       = nullptr;
}


Dolphin::StandardComponent::Direct2DRenderer::~Direct2DRenderer()
{
    this->SafeRelease(&this->backBuffer);
    this->SafeRelease(&this->dxgiSurface);
    this->SafeRelease(&this->dxgiSwapChain);
    this->SafeRelease(&this->dxgiFactory);
    this->SafeRelease(&this->dxgiAdapter);
    this->SafeRelease(&this->d2dDevice);
    this->SafeRelease(&this->d2dDeviceContext);
    this->SafeRelease(&this->d2dFactory);
    this->SafeRelease(&this->dxgiDevice);
    this->SafeRelease(&this->d3dDevice);
}


void Dolphin::StandardComponent::Direct2DRenderer::Start()
{
    // レンダーターゲットを作成
    auto window        = this->object->GetComponent<Window>();
    this->windowHandle = window->WindowHandle();


    RECT rectangle;
    GetClientRect(this->windowHandle, &rectangle);
    D2D1_SIZE_U size = D2D1::SizeU(
        rectangle.right - rectangle.left,
        rectangle.bottom - rectangle.top);

    auto d2dProperty = D2D1_RENDER_TARGET_PROPERTIES();
    d2dProperty.dpiX = 96;
    d2dProperty.dpiY = 96;

    DXGI_SWAP_CHAIN_DESC1 desc = { 0 };
    desc.Width                 = 0;
    desc.Height                = 0;
    desc.Format                = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.Stereo                = false;
    desc.SampleDesc.Count      = 1;
    desc.SampleDesc.Quality    = 0;
    desc.BufferUsage           = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount           = 2;
    desc.Scaling               = DXGI_SCALING_NONE;
    desc.SwapEffect            = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    desc.AlphaMode             = DXGI_ALPHA_MODE_UNSPECIFIED;
    desc.Flags                 = 0;

    D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
        D2D1::PixelFormat(
            DXGI_FORMAT_B8G8R8A8_UNORM,
            D2D1_ALPHA_MODE_IGNORE
        ),
        96.0f,
        96.0f
    );

    HRESULT result;

    result = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &this->d3dDevice,
        nullptr,
        nullptr
    );

    if (SUCCEEDED(result))
        result = this->d3dDevice->QueryInterface(&this->dxgiDevice);

    if (SUCCEEDED(result))
        result = this->dxgiDevice->SetMaximumFrameLatency(1);

    if (SUCCEEDED(result))
    {
        result = D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,
            &this->d2dFactory
        );
    }

    if (SUCCEEDED(result))
        result = this->d2dFactory->CreateDevice(this->dxgiDevice, &this->d2dDevice);

    if (SUCCEEDED(result))
    {
        result = this->d2dDevice->CreateDeviceContext(
            D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
            &this->d2dDeviceContext
        );
    }

    if (SUCCEEDED(result))
        result = this->dxgiDevice->GetAdapter(&this->dxgiAdapter);

    if (SUCCEEDED(result))
        result = this->dxgiAdapter->GetParent(IID_PPV_ARGS(&this->dxgiFactory));

    if (SUCCEEDED(result))
    {
        result = this->dxgiFactory->CreateSwapChainForHwnd(
            this->dxgiDevice,
            this->windowHandle,
            &desc,
            nullptr,
            nullptr,
            &this->dxgiSwapChain
        );
    }

    if (SUCCEEDED(result))
        result = this->dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&this->dxgiSurface));

    if (SUCCEEDED(result))
    {
        result = this->d2dDeviceContext->CreateBitmapFromDxgiSurface(
            this->dxgiSurface,
            &bitmapProperties,
            &this->backBuffer
        );
    }
}


void Dolphin::StandardComponent::Direct2DRenderer::Tick()
{
    this->d2dDeviceContext->SetTarget(this->backBuffer);
    this->d2dDeviceContext->BeginDraw();

    this->d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
    this->d2dDeviceContext->Clear(D2D1::ColorF(D2D1::ColorF::Blue));
}


void Dolphin::StandardComponent::Direct2DRenderer::LateTick()
{
    HRESULT result;
    DXGI_PRESENT_PARAMETERS params = {0};
    result = this->d2dDeviceContext->EndDraw();
    this->dxgiSwapChain->Present1(0, 0, &params);
}

ID2D1DeviceContext*
Dolphin::StandardComponent::Direct2DRenderer::DeviceContext()
{
    return this->d2dDeviceContext;
}