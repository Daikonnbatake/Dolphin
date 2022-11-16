#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"
#include "Component.h"
#define DELL(object) DolphinCore::Object::Destroy(object)

namespace Dolphin
{
	namespace Core
	{
		class Object
		{
		private:
			string name;
			bool onStart;
			bool isActive;
			vector<Component*>* components;

			Object(string name);
			virtual ~Object();
			void Start();



		public:
			static Object* Instantiate(string name);
			static void Destroy(Object* target);
			bool IsActive();
			void Enable();
			void Disable();
			string Name();

			template<class T> inline T* AddComponent()
			{
				T* component = new T(this);
				this->components->push_back(component);
				return component;
			}
			template<class T> inline T* GetComponent()
			{
				FOREACH(e, *this->components)
				{
					T* tmp = dynamic_cast<T*>(e);
					if (tmp != nullptr) return tmp;
				}
				return nullptr;
			}
			template<class T> inline vector<T*> GetComponents()
			{
				vector<T*> components;
				FOREACH(e, *this->components)
				{
					T* tmp = dynamic_cast<T*>(e);
					if (tmp != nullptr) components.push_back(tmp);
				}
				return components;
			}
			void PopComponent(Component* target);

			void Tick();
		};
	}
}