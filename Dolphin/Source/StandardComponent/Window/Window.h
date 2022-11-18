#pragma once
#include <windows.h>
#include "DolphinCore.h"
#include "DolphinStruct.h"
#include "DolphinStd.h"


namespace Dolphin
{
	namespace StandardComponent
	{
		class Window : public Dolphin::Core::Component
		{
		private:
			HWND parentHandle;
			bool closed;
			long windowStyle;
			HWND windowHandle;
			HINSTANCE instanceHandle;
			WNDCLASS windowClass;
			string className;
			string windowName;
			Dolphin::Struct::Vector2 position;
			Dolphin::Struct::Vector2 size;
			function<LRESULT(HWND, UINT, WPARAM, LPARAM)> thirdWindowProcedure;


			void Start() override;
			void Quit();
			HWND WindowHandle();
			void GenerateWindowClass(WNDCLASS& target);
			LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT message, WPARAM wordParam, LPARAM longParam);
			static LRESULT CALLBACK StaticWindowProc(HWND windowHandle, UINT message, WPARAM wordParam, LPARAM longParam);

		public:
			Window(Dolphin::Core::Object* object);
			bool Closed();
			Dolphin::Struct::Vector2& Position();
			Dolphin::Struct::Vector2& Size();
			string Title();
			void Title(string title);
			void Style(long windowStyle);
			void Tick() override;
		};
	}
}