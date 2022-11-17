#pragma once
#include "Object.h"
#include "Component.h"
#include "ObjectBuilder.h"
#include "../Component/Nest.h"


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