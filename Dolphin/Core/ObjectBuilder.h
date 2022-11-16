#pragma once
#include "DolphinMacro.h"
#include "Object.h"
#include "Component.h"
#include "Component/Nest.h"
#define New(name) Dolphin::ObjectBuilder::Instantiate(name)


namespace Dolphin
{
	class ObjectBuilder
	{
	private:
		class BuilderChain
		{
		private:
			DolphinCore::Object* object;
			DolphinSC::Nest* nest;

		public:
			inline BuilderChain(DolphinCore::Object* object)
			{
				this->object = object;
				this->nest = this->object->AddComponent<DolphinSC::Nest>();
			};
			inline operator DolphinCore::Object*() { return this->object; };

			inline BuilderChain& Child(BuilderChain obj)
			{
				obj.object->GetComponent<DolphinSC::Nest>()->MoveTo(this->object);
				return *this;
			};
			template<class T> inline BuilderChain& AddComponent()
			{
				this->object->AddComponent<T>();
				return *this;
			};
		};

	public:
		static inline BuilderChain Instantiate(string name)
		{
			return BuilderChain(DolphinCore::Object::Instantiate(name));
		};
	};
}