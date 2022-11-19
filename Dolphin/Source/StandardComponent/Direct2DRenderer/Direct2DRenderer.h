#pragma once
#pragma comment(lib, "d2d1" )
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include "DolphinCore.h"
#include "DolphinStd.h"
#include "Source/StandardComponent/Window/Window.h"


namespace Dolphin
{
	namespace StandardComponent
	{
		class Direct2DRenderer : public Dolphin::Core::Component
		{
		private:
			HWND windowHandle;
			ID2D1Factory* direct2DFactory;
			ID2D1HwndRenderTarget* renderTarget;
			function<void(void)> OnRendering;

			void Start() override;
			LRESULT WindowProcedure(HWND windowHandle, UINT message, WPARAM wordParam, LPARAM longParam);

		public:
			Direct2DRenderer(Dolphin::Core::Object* object);
			~Direct2DRenderer();
			template<class Interface> void SafeRelease(Interface **target);
		};
	}
}