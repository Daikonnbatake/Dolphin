#pragma once
#include "DolphinStd.h"
#include "Source/Core/Component/Component_member.h"
#include "Source/StandardComponent/Nest_forward.h"
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
			Dolphin::StandardComponent::Nest* nest;

			Object(string name);
			virtual ~Object();
			void Start();


		public:
			static Object* Instantiate(string name);
			static void Destroy(Object* target);

			Dolphin::StandardComponent::Nest* Nest();
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