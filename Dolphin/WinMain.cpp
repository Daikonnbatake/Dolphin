#include <Windows.h>
#include "Dolphin.h"


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