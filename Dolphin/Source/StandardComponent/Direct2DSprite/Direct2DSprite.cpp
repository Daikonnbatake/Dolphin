#include "Direct2DSprite.h"

Dolphin::StandardComponent::Direct2DSprite::Direct2DSprite(Core::Object* object)
    : Component(object)
{
    if (FAILED(CoInitialize(nullptr))) return;

	CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory,
        (LPVOID*)&factory
	);

    this->factory->CreateDecoderFromFilename(
        L"../Dolphin/Application/Resource/dummy.png",
        nullptr,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &decoder
    );

    this->decoder->GetFrame(0, &frame);
    this->factory->CreateFormatConverter(&formatConverter);
    formatConverter->Initialize(
        this->frame,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr,
        1.0f,
        WICBitmapPaletteTypeMedianCut
    );
}


Dolphin::StandardComponent::Direct2DSprite::~Direct2DSprite()
{
    this->factory->Release();
    this->decoder->Release();
    this->frame->Release();
    this->formatConverter->Release();
    CoUninitialize();
}


void Dolphin::StandardComponent::Direct2DSprite::Start()
{
    this->renderTarget = this->object->Nest()->Parent()->GetComponent<Direct2DRenderer>()->Rendertarget();
    this->windowHandle = this->object->Nest()->Parent()->GetComponent<Window>()->WindowHandle();

    this->renderTarget->CreateBitmapFromWicBitmap(
        formatConverter,
        nullptr,
        &bitmap);
}


void Dolphin::StandardComponent::Direct2DSprite::Tick()
{
    RECT rect;
    GetClientRect(this->windowHandle, &rect);
    D2D1_SIZE_U size = D2D1::SizeU(rect.right, rect.bottom);
    float dpi        = GetDpiForWindow(this->windowHandle);
    float dpiScaling = dpi / 96.0f;

    this->renderTarget->DrawBitmap(
        bitmap,
        D2D1::RectF(
            rect.left * dpiScaling,
            rect.top * dpiScaling,
            rect.right * dpiScaling,
            rect.bottom * dpiScaling),
        1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
        nullptr
    );
}