#pragma once
#include "Core.h"
#include "Object.h"

namespace Dolphin
{
	namespace Core
	{
		class Application
		{
		// 隠しフィールド
		private:
			Object* rootObject;


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