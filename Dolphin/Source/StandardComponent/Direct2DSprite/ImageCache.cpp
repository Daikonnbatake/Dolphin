#include "Direct2DSprite.h"


Dolphin::StandardComponent::Direct2DSprite::ImageCache::ImageCache(
    ID2D1DeviceContext* deviceContext)
{
    this->deviceContext = deviceContext;
    this->factory      = nullptr;
    this->cache        = unordered_map<string, ID2D1Bitmap1*>();

    HRESULT result;
    if (FAILED(CoInitialize(nullptr))) return;

    result = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory,
        (LPVOID*)&this->factory
    );
    if (FAILED(result)) return;
}


Dolphin::StandardComponent::Direct2DSprite::ImageCache::~ImageCache()
{
    auto begin = this->cache.begin();
    auto end   = this->cache.end();
    for (auto itr = begin; itr != end; ++itr)
    {
        itr->second->Release();
        itr->second = nullptr;
    }

    this->factory->Release();
    this->factory = nullptr;

    CoUninitialize();
}


ID2D1Bitmap1*
Dolphin::StandardComponent::Direct2DSprite::ImageCache::Bitmap(string path)
{
    // キャッシュがあるときはキャッシュを使う
    auto findResult = this->cache.find(path);
    if (findResult != this->cache.end()) return findResult->second;

    // キャッシュが無い時は生成する
    HRESULT                result;
    IWICBitmapDecoder*     decoder   = nullptr;
    IWICBitmapFrameDecode* frame     = nullptr;
    IWICFormatConverter*   converter = nullptr;
    ID2D1Bitmap1*          bitmap    = nullptr;

    result = this->factory->CreateDecoderFromFilename(
        path.c_str(),
        nullptr,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &decoder
    );

    if (SUCCEEDED(result)) result = decoder->GetFrame(0, &frame);
    if (SUCCEEDED(result)) result = factory->CreateFormatConverter(&converter);

    if (SUCCEEDED(result))
    {
        result = converter->Initialize(
            frame,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            1.0f,
            WICBitmapPaletteTypeMedianCut
        );
    }

    if (SUCCEEDED(result))
    {
        result = this->deviceContext->CreateBitmapFromWicBitmap(
            converter,
            nullptr,
            &bitmap
        );
    }

    SafeRelease(&decoder);
    SafeRelease(&frame);
    SafeRelease(&converter);

    if (FAILED(result)) return nullptr;

    this->cache[path] = bitmap;
    return bitmap;
}