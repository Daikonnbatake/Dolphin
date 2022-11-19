#include "Window.h"


Dolphin::StandardComponent::Window::Window(Dolphin::Core::Object* object) : Component(object)
{
	this->closed = false;
	this->className = this->object->Name();
	this->windowName = "いるかエンジン - " + this->className;
	this->instanceHandle = ((HINSTANCE)GetModuleHandle(0));
	this->thirdWindowProcedure = nullptr;
	this->windowClass = { 0 };
	this->GenerateWindowClass(this->windowClass);
	RegisterClass(&(this->windowClass));
}


bool Dolphin::StandardComponent::Window::Closed() { return this->closed; }
void Dolphin::StandardComponent::Window::Quit() { this->closed = true; }
HWND Dolphin::StandardComponent::Window::WindowHandle() { return this->windowHandle; }
void Dolphin::StandardComponent::Window::Title(string title) { this->windowName = title; }
void Dolphin::StandardComponent::Window::Style(long windowStyle) { this->windowStyle = windowStyle; }
std::string Dolphin::StandardComponent::Window::Title() { return this->windowName; }
Dolphin::Struct::Vector2& Dolphin::StandardComponent::Window::Position() { return this->position; }
Dolphin::Struct::Vector2& Dolphin::StandardComponent::Window::Size() { return this->size; }
void Dolphin::StandardComponent::Window::ThirdWindowProcedure(function<LRESULT(HWND, UINT, WPARAM, LPARAM)> windowProc) { this->thirdWindowProcedure = windowProc; }


void Dolphin::StandardComponent::Window::GenerateWindowClass(WNDCLASS& target)
{
	target.lpfnWndProc = StaticWindowProc;
	target.hInstance = instanceHandle;
	target.style = CS_HREDRAW | CS_VREDRAW;
	target.cbClsExtra = 0;
	target.cbWndExtra = 0;
	target.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	target.hCursor = LoadCursor(NULL, IDC_ARROW);
	target.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	target.lpszMenuName = NULL;
	target.lpszClassName = this->className.c_str();
}


LRESULT CALLBACK Dolphin::StandardComponent::Window::WindowProcedure(HWND windowHandle, UINT message, WPARAM wordParam, LPARAM longParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			this->closed = true;
			PostQuitMessage(0);
			break;
		}
	}

	if (this->thirdWindowProcedure != nullptr)
	{
		this->thirdWindowProcedure(windowHandle, message, wordParam, longParam);
	}

	return DefWindowProc(windowHandle, message, wordParam, longParam);
}


LRESULT CALLBACK Dolphin::StandardComponent::Window::StaticWindowProc(HWND windowHandle, UINT message, WPARAM wordParam, LPARAM longParam)
{
	Window* This = (Window*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);

	if (!This)
	{
		if (message == WM_CREATE)
		{
			This = (Window*)((LPCREATESTRUCT)longParam)->lpCreateParams;
			if (This)
			{
				SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)This);
				return This->WindowProcedure(windowHandle, message, wordParam, longParam);
			}
		}
	}
	else return This->WindowProcedure(windowHandle, message, wordParam, longParam);
	return DefWindowProc(windowHandle, message, wordParam, longParam);
}


void Dolphin::StandardComponent::Window::Start()
{
	// 親オブジェクトに window コンポーネントがある場合, それの子としてウィンドウを生成する.
	if (this->object->Nest()->Parent() != nullptr)
	{
		this->parentHandle = this->object->Nest()->Parent()->GetComponent<Window>()->WindowHandle();
	}
	else this->parentHandle = nullptr;


	this->windowHandle = CreateWindow(
		this->className.c_str(),
		this->windowName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		480, 320,
		((this->parentHandle != nullptr) ? this->parentHandle : NULL),
		NULL,
		this->instanceHandle,
		this
	);

	ShowWindow(this->windowHandle, SW_SHOW);
}


void Dolphin::StandardComponent::Window::Tick()
{
	MSG message = { 0 };
	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	else
	{
		// ゲームの処理

	}
}