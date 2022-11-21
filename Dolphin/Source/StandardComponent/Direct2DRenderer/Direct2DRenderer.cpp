#include "Direct2DRenderer.h"

#include "Direct2DRenderer_inline.h"


Dolphin::StandardComponent::Direct2DRenderer::Direct2DRenderer(
    Dolphin::Core::Object* object)
    : Component(object)
{
    this->windowHandle    = nullptr;
    this->direct2DFactory = nullptr;
    this->renderTarget    = nullptr;
    this->rendering       = nullptr;
}


Dolphin::StandardComponent::Direct2DRenderer::~Direct2DRenderer()
{
    this->SafeRelease(&renderTarget);
    this->SafeRelease(&this->direct2DFactory);
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

    D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &this->direct2DFactory);
    this->direct2DFactory->CreateHwndRenderTarget(
        d2dProperty,
        D2D1::HwndRenderTargetProperties(this->windowHandle, size),
        &this->renderTarget);
}


void Dolphin::StandardComponent::Direct2DRenderer::RenderingProcess(
    function<void(void)> renderingProcess)
{
    this->rendering = std::bind(&Direct2DRenderer::rendering, this);
}
ID2D1HwndRenderTarget*
Dolphin::StandardComponent::Direct2DRenderer::Rendertarget()
{
    return this->renderTarget;
}
