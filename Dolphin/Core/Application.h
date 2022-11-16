#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"
#include "ObjectBuilder.h"


namespace Dolphin
{
	namespace Core
	{
		class Application
		{
		private:
			Object* rootObject;
			bool quit;


		public:
			Application();
			~Application();
			void Tick();
			void Quit();
			bool IsQuit();
		};
	}
}