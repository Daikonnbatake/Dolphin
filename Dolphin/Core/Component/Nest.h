#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"
#include "../Component.h"
#include "../Object.h"

namespace Dolphin
{
	namespace StandardComponent
	{
		class Nest : public DolphinCore::Component
		{
		private:
			DolphinCore::Object* parent;
			vector<DolphinCore::Object*> children;

			Nest(DolphinCore::Object* object);
			~Nest() override;


		public:
			int ChildCount();
			DolphinCore::Object* Parent();
			DolphinCore::Object* MoveTo(DolphinCore::Object* target);
			DolphinCore::Object* AddChild(DolphinCore::Object* target);
			DolphinCore::Object* GetChild(string name);

			void Start() override;
		};
	}
}