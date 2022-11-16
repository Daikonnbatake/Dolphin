#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"


namespace Dolphin
{
	namespace Core
	{
		class Object;

		class Component
		{
		friend class Object;

		protected:
			Object* object;

			Component(Object* object);
			virtual ~Component(){};
			virtual void Start(){};
			virtual void Tick(){};


		public:
			Object* ThisObject();
		};
	}
}