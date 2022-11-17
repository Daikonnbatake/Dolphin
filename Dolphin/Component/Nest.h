#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"
#include "Component.h"
#include "Object.h"


namespace Dolphin
{
	namespace StandardComponent
	{
		class Object;
		class Nest : public Dolphin::Core::Component
		{
		private:
			Dolphin::Core::Object* parent;
			vector<Dolphin::Core::Object*> children;


		public:
			Nest(Dolphin::Core::Object* object);
			~Nest() override;
			int ChildCount();
			Dolphin::Core::Object* Parent();
			Dolphin::Core::Object* MoveTo(Dolphin::Core::Object* target);
			Dolphin::Core::Object* GetChild(string name);

			void Start() override {};
		};
	}
}