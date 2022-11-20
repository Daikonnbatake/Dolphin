#include "Direct2DRenderer.h"
#include "Direct2DRenderer_inline.h"


Dolphin::StandardComponent::Direct2DRenderer::Direct2DRenderer(Dolphin::Core::Object* object) : Component(object)
{
	this->windowHandle = nullptr;
	this->direct2DFactory = nullptr;
	this->renderTarget = nullptr;
	this->rendering = nullptr;
}


Dolphin::StandardComponent::Direct2DRenderer::~Direct2DRenderer()
{
	this->SafeRelease(&renderTarget);
	this->SafeRelease(&this->direct2DFactory);
}


void Dolphin::StandardComponent::Direct2DRenderer::Start()
{
	// レンダーターゲットを作成
	auto window = this->object->GetComponent<Window>();
	this->windowHandle = window->WindowHandle();
	window->ThirdWindowProcedure(
		std::bind(
			&Direct2DRenderer::WindowProcedure, this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4
		));

	RECT rectangle;
	GetClientRect(this->windowHandle, &rectangle);
	D2D1_SIZE_U size = D2D1::SizeU(rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->direct2DFactory);
	this->direct2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(this->windowHandle, size),
		&this->renderTarget
	);
}


LRESULT Dolphin::StandardComponent::Direct2DRenderer::WindowProcedure(HWND windowHandle, UINT message, WPARAM wordParam, LPARAM longParam)
{
	switch(message)
	{
		case WM_PAINT:
		{
			if (this->rendering != nullptr) this->rendering();
		}
	}
	return LRESULT();
}


void Dolphin::StandardComponent::Direct2DRenderer::RenderingProcess(function<void(void)> renderingProcess) { this->rendering = std::bind(&Direct2DRenderer::rendering, this); }
ID2D1HwndRenderTarget* Dolphin::StandardComponent::Direct2DRenderer::Rendertarget() { return this->renderTarget; }