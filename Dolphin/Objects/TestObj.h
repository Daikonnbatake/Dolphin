#pragma once
#include "Core.h"
#include "Object.h"
#include <iostream>

using std::cout;
using std::endl;

namespace Dolphin
{
	namespace Core
	{
		class TestObj : public Object
		{
		public:
			TestObj() : Object(){};
			~TestObj() override;

		public:
			void OnInit();
			void OnUpdate();
			void OnRender();
			void OnDestroy();
		};
	}
}