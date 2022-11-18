#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"
#include "Source/Core/Component/Component_member.h"
#include "Source/Core/Object/Object_inline.h"


namespace Dolphin
{
	namespace StandardComponent
	{
		class Nest : public Dolphin::Core::Component
		{
		private:
			Dolphin::Core::Object* parent;
			vector<Dolphin::Core::Object*> children;


		public:
			Nest(Dolphin::Core::Object* object);
			~Nest() override;
			void Tick() override;
			int ChildCount();
			Dolphin::Core::Object* Parent();
			Dolphin::Core::Object* MoveTo(Dolphin::Core::Object* target);
			Dolphin::Core::Object* GetChild(string name);
		};
	}
}