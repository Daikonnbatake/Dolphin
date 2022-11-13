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
		// 隠しフィールド
		private:
			Object* rootObject;
			TestComponent* test;


		public:
			Application();
			~Application();


		// 公開メソッド
		public:
			void Initialize();
			void Tick();
			void Release();
		};
	}
}