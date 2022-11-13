#pragma once
#include "Core.h"
#include "Object.h"
#include "../Objects/TestObj.h"
#include "../Objects/TestComponent.h"

namespace Dolphin
{
	namespace Core
	{
		class Application
		{
		// �B���t�B�[���h
		private:
			Object* rootObject;
			TestComponent* test;


		public:
			Application();
			~Application();


		// ���J���\�b�h
		public:
			void Initialize();
			void Tick();
			void Release();
		};
	}
}