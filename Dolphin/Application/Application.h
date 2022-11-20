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
	class Application;
	Core::Object* InitObjectTree();
	void Start(Application& app);
	void Update(Application& app);
	void Rendering(Application& app);
	void Release(Application& app);

	class Application
	{
	private:
		Core::Object* rootObject;
		bool quit;
		bool init;
		void Start();


	public:
		Application();
		~Application();
		Dolphin::Core::Object* Root();
		void Tick();
		void Quit();
		bool IsQuit();
	};
}