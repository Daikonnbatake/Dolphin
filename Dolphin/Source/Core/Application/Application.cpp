#include "Application_member.h"
#include "Core/ObjectBuilder.h"
#include "DolphinStandardComponent.h"

Dolphin::Core::Application::Application()
{
	using namespace Dolphin::StandardComponent;
	this->quit = false;
	this->init = false;

	// デバッグ用画像表示やつ初期化
	this->filename = L"G:\\image.bmp";
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


	this->factory->CreateDecoderFromFilename(
		this->filename,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&this->decoder
	);

	this->decoder->GetFrame(0, &this->frame);

	this->factory->CreateFormatConverter(&this->formatConverter);

	this->formatConverter->Initialize(
		this->frame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		1.0f,
		WICBitmapPaletteTypeMedianCut
	);

	d2d->Rendertarget()->CreateBitmapFromWicBitmap(
		this->formatConverter,
		nullptr,
		&this->bitmap
	);
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
	D2D1_SIZE_U size = D2D1::SizeU(rect.right, rect.bottom);
	renderTarget->Resize(size);
	float dpi = GetDpiForWindow(window->WindowHandle());
	float dpiScaling = dpi / 96.0f;
	renderTarget->BeginDraw();

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Blue));

	renderTarget->DrawBitmap(
		this->bitmap,
		D2D1::RectF(
			rect.left * dpiScaling,
			rect.top * dpiScaling,
			rect.right * dpiScaling,
			rect.bottom * dpiScaling
		),
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