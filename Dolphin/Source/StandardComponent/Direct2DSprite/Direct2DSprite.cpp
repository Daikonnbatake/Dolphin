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

    this->renderTarget = nullptr;
    this->spriteRect = D2D1::RectF(0, 0, 255, 255);
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
}


void Dolphin::StandardComponent::Direct2DSprite::Start()
{
    this->renderTarget = this->object->Nest()->Parent()->GetComponent<Direct2DRenderer>()->Rendertarget();
    (*this->imageCache)[this->renderTarget] = new ImageCache(this->renderTarget);
}


void Dolphin::StandardComponent::Direct2DSprite::Tick()
{
    ID2D1Bitmap* bitmap = (*imageCache)[this->renderTarget]->Bitmap(this->path);
    if (bitmap == nullptr) return;

    this->renderTarget->DrawBitmap(
        bitmap,
        this->spriteRect,
        1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
        nullptr
    );
}