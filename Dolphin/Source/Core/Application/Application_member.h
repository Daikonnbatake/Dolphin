#pragma once
#pragma comment(lib, "d2d1" )
#pragma comment(lib,"windowscodecs.lib")
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "Core/Object.h"
#include "Core/Component.h"


namespace Dolphin
{
	namespace Core
	{
		class Application
		{
		private:
			Object* rootObject;
			bool quit;
			bool init;

			// デバッグ用
			LPCWSTR filename;
			IWICImagingFactory* factory;
			IWICBitmapDecoder* decoder;
			IWICBitmapFrameDecode* frame;
			IWICFormatConverter* formatConverter;
			ID2D1Bitmap* bitmap;
			void Start();


		public:
			Application();
			~Application();
			void Tick();
			void Quit();
			bool IsQuit();
		};
	}
}