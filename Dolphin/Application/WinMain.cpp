﻿#include <Windows.h>
#include "Dolphin.h"
#include "Application.h"


namespace Dolphin
{
	// デバッグ用
	LPCWSTR filename;
	IWICImagingFactory* factory;
	IWICBitmapDecoder* decoder;
	IWICBitmapFrameDecode* frame;
	IWICFormatConverter* formatConverter;
	ID2D1Bitmap* bitmap;
	Dolphin::StandardComponent::Window* rootWindow;


	Dolphin::Core::Object* InitObjectTree()
	{
		return NEW(L"root")
			.AddComponent<Transform2D>()
			.AddComponent<Window>()
			.AddComponent<Direct2DRenderer>()
			.Child(
				NEW(L"ObjectA")
				.AddComponent<Transform2D>()
				//.AddComponent<Window>()
				//.AddComponent<Direct2DRenderer>()
				.Child(
					NEW(L"ObjectAA")
					.AddComponent<Transform2D>()
					//.AddComponent<Window>()
					//.AddComponent<Direct2DRenderer>()
				)
				.Child(
					NEW(L"ObjectAB")
					.AddComponent<Transform2D>()
					//.AddComponent<Window>()
					//.AddComponent<Direct2DRenderer>()
					.Child(
						NEW(L"ObjectABA")
						.AddComponent<Transform2D>()
						//.AddComponent<Window>()
						//.AddComponent<Direct2DRenderer>()
					)
				)
			);
	}


	void Start(Application& app)
	{
		using namespace Dolphin::StandardComponent;

		// デバッグ用画像表示やつ初期化
		filename = L"G:\\image.bmp";
		factory = nullptr;
		decoder = nullptr;
		frame = nullptr;
		formatConverter = nullptr;
		bitmap = nullptr;

		// デバッグ用画像表示やつに渡すコンポーネント
		auto d2d = app.Root()->GetComponent<Direct2DRenderer>();
		auto window = app.Root()->GetComponent<Window>();
		rootWindow = window;


		if (FAILED(CoInitialize(nullptr))) return;
		HRESULT result = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&factory);
		if (FAILED(result)) return;

		factory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
		decoder->GetFrame(0, &frame);
		factory->CreateFormatConverter(&formatConverter);
		formatConverter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 1.0f, WICBitmapPaletteTypeMedianCut);
		d2d->Rendertarget()->CreateBitmapFromWicBitmap(formatConverter, nullptr, &bitmap);
	}


	void Update(Application& app)
	{
		if (rootWindow->Closed()) app.Quit();
	}


	void Rendering(Application& app)
	{
		using namespace Dolphin::StandardComponent;

		auto window = app.Root()->GetComponent<Window>();
		auto d2d = app.Root()->GetComponent<Direct2DRenderer>();

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
			bitmap,
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
	}


	void Release(Application& app)
	{
		// デバッグ用画像表示やつ解放
		factory->Release();
		decoder->Release();
		frame->Release();
		formatConverter->Release();
		CoUninitialize();
	}
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Application app;
	Angle a = Angle(50);
	double b = a.Degree();

	while (!app.IsQuit())
	{
		app.Tick();
	}
	return 0;
}