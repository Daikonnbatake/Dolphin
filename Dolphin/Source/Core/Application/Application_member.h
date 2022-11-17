#pragma once
#include "Core/Object.h"
#include "Core/Component.h"
#include "Core/ObjectBuilder.h"
#include "DolphinStandardComponent.h"


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