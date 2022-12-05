#include "Direct2DSprite.h"

std::unordered_map<ID2D1RenderTarget*, Dolphin::StandardComponent::Direct2DSprite::ImageCache*>*
    Dolphin::StandardComponent::Direct2DSprite::imageCache;


Dolphin::StandardComponent::Direct2DSprite::Direct2DSprite(Core::Object* object)
    : Component(object)
{
    if (imageCache == nullptr)
    {
        this->imageCache = new unordered_map<ID2D1RenderTarget*, ImageCache*>();
    }

    this->matrix = D2D1::Matrix3x2F::Identity();
    this->bitmap = nullptr;
    this->deviceContext = nullptr;
    this->spriteRect   = D2D1::RectF();
    this->clippingRect = D2D1::RectF();
}


Dolphin::StandardComponent::Direct2DSprite::~Direct2DSprite()
{
    if (this->imageCache != nullptr)
    {
        delete this->imageCache;
        this->imageCache = nullptr;
    }
}


void Dolphin::StandardComponent::Direct2DSprite::ImagePath(string path)
{
    this->path = path;
    this->bitmap = (*imageCache)[this->deviceContext]->Bitmap(this->path);
    if (this->bitmap == nullptr) return;
    const D2D1_SIZE_U& size = this->bitmap->GetPixelSize();
    this->spriteRect = D2D1::RectF(0, 0, size.width - 1, size.height - 1);
    this->clippingRect = D2D1::RectF(0, 0, size.width - 1, size.height - 1);
}


void Dolphin::StandardComponent::Direct2DSprite::AffineTransform(
    AffineBuilder affineBuilder)
{
    this->matrix = affineBuilder.ReadMatrix();
}


void Dolphin::StandardComponent::Direct2DSprite::Clipping(
    float left,
    float top,
    float right,
    float bottom)
{
    this->clippingRect = D2D1::RectF(left, top, right, bottom);
    this->spriteRect = D2D1::RectF(0, 0, right - left, bottom - top);
}


void Dolphin::StandardComponent::Direct2DSprite::ClearClipping()
{
    const D2D1_SIZE_U& size = this->bitmap->GetPixelSize();
    this->spriteRect   = D2D1::RectF(0, 0, size.width - 1, size.height - 1);
    this->clippingRect = D2D1::RectF(0, 0, size.width - 1, size.height - 1);
}


D2D1_RECT_F Dolphin::StandardComponent::Direct2DSprite::CropRect()
{
    return this->clippingRect;
}


void Dolphin::StandardComponent::Direct2DSprite::Start()
{
    this->deviceContext = this->object->Nest()->Parent()->GetComponent<Direct2DRenderer>()->DeviceContext();
    (*this->imageCache)[this->deviceContext] = new ImageCache(this->deviceContext);
}


void Dolphin::StandardComponent::Direct2DSprite::Tick()
{
    if (this->bitmap == nullptr) return;
    ID2D1Effect* crop = nullptr;
    ID2D1Effect* transform = nullptr;
    D2D1_MATRIX_3X2_F offset = D2D1::Matrix3x2F::Translation(
        D2D1::SizeF(
            -this->clippingRect.left,
            -this->clippingRect.top
        )
    );

    this->deviceContext->CreateEffect(CLSID_D2D1Crop, &crop);
    crop->SetInput(0, this->bitmap);
    crop->SetValue(D2D1_CROP_PROP_RECT, this->clippingRect);

    this->deviceContext->CreateEffect(CLSID_D2D12DAffineTransform, &transform);
    transform->SetInputEffect(0, crop);
    transform->SetValue(
        D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX,
        this->matrix * offset
    );
    transform->SetValue(
        D2D1_2DAFFINETRANSFORM_PROP_INTERPOLATION_MODE,
        D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_NEAREST_NEIGHBOR
    );

    this->deviceContext->DrawImage(transform);

    if (transform != nullptr)
    {
        transform->Release();
        transform = nullptr;
    }

    if (crop != nullptr)
    {
        crop->Release();
        crop = nullptr;
    }
}