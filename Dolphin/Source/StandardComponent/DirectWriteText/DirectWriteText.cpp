#include "pch.h"
#include "DirectWriteText.h"


Dolphin::StandardComponent::DirectWriteText::DirectWriteText(Core::Object* object)
    : Component(object)
{
    this->text = L"‚³‚ñ‚Õ‚é‚à‚¶‚ê‚Â";
    this->fontFamilyName = L"Arial";
    this->color = D2D1::ColorF(D2D1::ColorF::White);
    this->fontSize = 24.0f;
    this->deviceContext == nullptr;
    this->factory = nullptr;
    this->format = nullptr;
    this->brush = nullptr;
}


Dolphin::StandardComponent::DirectWriteText::~DirectWriteText()
{
    this->brush->Release();
    this->brush = nullptr;
    this->format->Release();
    this->format = nullptr;
    this->factory->Release();
    this->factory = nullptr;
}


void Dolphin::StandardComponent::DirectWriteText::Start()
{
    HRESULT result;
    this->deviceContext = this->object->Nest()->Parent()->GetComponent<Direct2DRenderer>()->DeviceContext();
    this->windowHandle = this->object->Nest()->Parent()->GetComponent<Window>()->WindowHandle();

    if (this->deviceContext == nullptr) return;

    result = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&this->factory)
    );

    if (SUCCEEDED(result))
    {
        result = this->factory->CreateTextFormat(
            this->fontFamilyName.c_str(),
            nullptr,
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            this->fontSize,
            L"ja-jp",
            &this->format
        );
    }

    if (SUCCEEDED(result))
    {
        result = this->deviceContext->CreateSolidColorBrush(
            this->color,
            &this->brush
        );
    }
}


void Dolphin::StandardComponent::DirectWriteText::Tick()
{
    RECT rect;
    GetClientRect(this->windowHandle, &rect);
    D2D1_RECT_F layoutRect = D2D1::RectF(
        static_cast<FLOAT>(rect.left),
        static_cast<FLOAT>(rect.top),
        static_cast<FLOAT>(rect.right),
        static_cast<FLOAT>(rect.bottom)
    );

    this->deviceContext->DrawTextW(
        this->text.c_str(),
        this->text.size(),
        this->format,
        layoutRect,
        this->brush
    );
}