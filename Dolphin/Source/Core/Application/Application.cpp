#include "Application_member.h"
#include "Core/ObjectBuilder.h"
#include "DolphinStandardComponent.h"

Dolphin::Core::Application::Application()
{
	using namespace Dolphin::StandardComponent;
	this->quit = false;
	this->init = false;

	// デバッグ用画像表示やつ初期化
	this->filename = L"G:\\image.png";
	this->factory = nullptr;
	this->decoder = nullptr;
	this->frame = nullptr;
	this->formatConverter = nullptr;
	this->bitmap = nullptr;


	// オブジェクトツリーの定義
	this->rootObject = New(L"root")
		.AddComponent<Transform2D>()
		.AddComponent<Window>()
		.AddComponent<Direct2DRenderer>()
		.Child(
			New(L"ObjectA")
			.AddComponent<Transform2D>()
			//.AddComponent<Window>()
			//.AddComponent<Direct2DRenderer>()
			.Child(
				New(L"ObjectAA")
				.AddComponent<Transform2D>()
				//.AddComponent<Window>()
				//.AddComponent<Direct2DRenderer>()
			)
			.Child(
				New(L"ObjectAB")
				.AddComponent<Transform2D>()
				//.AddComponent<Window>()
				//.AddComponent<Direct2DRenderer>()
				.Child(
					New(L"ObjectABA")
					.AddComponent<Transform2D>()
					//.AddComponent<Window>()
					//.AddComponent<Direct2DRenderer>()
				)
			)
		);
}

void Dolphin::Core::Application::Start()
{
	using namespace Dolphin::StandardComponent;

	// デバッグ用画像表示やつに渡すコンポーネント
	auto d2d = this->rootObject->GetComponent<Direct2DRenderer>();
	auto window = this->rootObject->GetComponent<Window>();


	if (FAILED(CoInitialize(nullptr))) return;

	HRESULT result = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&this->factory
	);
	if (FAILED(result)) return;


	result = this->factory->CreateDecoderFromFilename(
		this->filename,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&this->decoder
	);
	if (FAILED(result)) return;

	result = this->decoder->GetFrame(0, &this->frame);
	if (FAILED(result)) return;

	result = this->factory->CreateFormatConverter(&this->formatConverter);
	if (FAILED(result)) return;

	result = this->formatConverter->Initialize(
		this->frame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		1.0f,
		WICBitmapPaletteTypeMedianCut
	);
	if (FAILED(result)) return;

	result = d2d->Rendertarget()->CreateBitmapFromWicBitmap(
		this->formatConverter,
		nullptr,
		&this->bitmap
	);
	if (FAILED(result)) return;
}


void Dolphin::Core::Application::Tick()
{
	this->rootObject->Tick();

	// 初期化
	if (!this->init)
	{
		this->Start();
		this->init = true;
	}

	auto window = this->rootObject->GetComponent<Dolphin::StandardComponent::Window>();
	auto d2d = this->rootObject->GetComponent<Dolphin::StandardComponent::Direct2DRenderer>();

	ID2D1HwndRenderTarget* renderTarget = d2d->Rendertarget();
	RECT rect;
	GetClientRect(window->WindowHandle(), &rect);

	renderTarget->BeginDraw();

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Blue));

	renderTarget->DrawBitmap(
		this->bitmap,
		D2D1::RectF(rect.left, rect.top, rect.right, rect.bottom),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		nullptr
	);

	renderTarget->EndDraw();


	if (window->Closed())
	{
		this->Quit();
	}
}


Dolphin::Core::Application::~Application()
{
	DELL(this->rootObject);

	// デバッグ用画像表示やつ解放
	this->factory->Release();
	this->decoder->Release();
	this->frame->Release();
	this->formatConverter->Release();
	CoUninitialize();
}


void Dolphin::Core::Application::Quit() { this->quit = true; }
bool Dolphin::Core::Application::IsQuit() { return this->quit; }