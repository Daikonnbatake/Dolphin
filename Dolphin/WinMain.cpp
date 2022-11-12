#include <Windows.h>


HWND windowHandle;
LPCWSTR className = L"DolphinApp";
LPCWSTR windowName = L"DolphinApp";
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASS windowClass = {0};
	MSG message = {0};
	windowClass.lpfnWndProc = WindowProcedure;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = className;
	RegisterClass(&windowClass);

	windowHandle = CreateWindow(
		className,
		windowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (windowHandle == NULL) return 0;

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			// ÉQÅ[ÉÄÇÃèàóù
		}
	}

	return 0;
}


LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT message, WPARAM wordParam, LPARAM longParam)
{
	switch (message)
	{
		case WM_CREATE:
			{
				return 0;
			}

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
	}

	return DefWindowProc(windowHandle, message, wordParam, longParam);
}