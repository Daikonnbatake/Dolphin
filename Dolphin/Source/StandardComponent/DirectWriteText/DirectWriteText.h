#pragma once
#pragma comment(lib, "Dwrite.lib")
#include "DolphinCore.h"
#include "../Direct2DRenderer/Direct2DRenderer.h"
#include "../Window/Window.h"
#include <d2d1_1.h>
#include <dwrite_1.h>

namespace Dolphin
{
	namespace StandardComponent
	{
		class DirectWriteText : public Core::Component
		{
		private:
			string text;
			string fontFamilyName;
			float fontSize;
			D2D1_COLOR_F color;
			HWND windowHandle;
			ID2D1DeviceContext* deviceContext;
			IDWriteFactory1*    factory;
			IDWriteTextFormat*  format;
			ID2D1SolidColorBrush* brush;

			void Start() override;
			void Tick() override;

		public:
			DirectWriteText(Core::Object* object);
			~DirectWriteText();
		};
	}
}
