#pragma once
#include "DolphinStd.h"
#include "Component.h"
#include "Object_forward.h"


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
			void PopComponent(Component* target);
			void Tick();

			template<class T> T* AddComponent();
			template<class T> T* GetComponent();
			template<class T> vector<T*> GetComponents();
		};
	}
}