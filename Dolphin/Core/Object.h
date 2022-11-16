#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"
#include "Component.h"
#define NEW(name) Dolphin::Core::Object::Instantiate(name)
#define DELL(name) Dolphin::Core::Object::Destroy(name)


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
			bool IsActive();
			void Enable();
			void Disable();
			string Name();

			static Object* Instantiate(string name);
			static void Destroy(Object* target);

			template<class T> T* AddComponent();
			template<class T> T* GetComponent();
			template<class T> vector<T*> GetComponents();
			void PopComponent(Component* target);

			void Tick();
		};
	}
}