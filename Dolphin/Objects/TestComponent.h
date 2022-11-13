#pragma once
#include "Core.h"
#include "Object.h"
#include "Component.h"

namespace Dolphin
{
	namespace Core
	{
		class TestComponent : public Component
		{
		public:
			TestComponent(Object* parent) : Component(parent){};
			~TestComponent() override {};

			string Hoge() { return "Hoge"; };
			string Foo(){ return "Foo"; };
		};
	}
}