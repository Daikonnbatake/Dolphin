#pragma once
#include "Core.h"
#include "Component.h"

namespace Dolphin
{
	namespace Core
	{
		class Object
		{
		// 隠しフィールド
		private:
			bool					isActive;
			Object*					parent;
			string					name;
			vector<Object*>			children;
			vector<Component*>		components;

		public:
			// コンストラクタ
			Object();
			Object(string name);

			// デストラクタ
			virtual ~Object();


			// getter
			bool		IsActive();
			bool		IsRoot();
			Object*		Parent();
			string		Name();


			// 公開メソッド
			static void								Destroy(Object* target);
			static void								Destroy(Component* target);
			bool									operator==(const Object& obj);
			bool									operator!=(const Object& obj);

			template<class T> T* AddComponent()
			{
				T* component = new T(this);
				this->components.push_back(dynamic_cast<Component*>(component));
				return component;
			};

			template<class T> T* GetComponent()
			{
				FOREACH(e, this->components)
				{
					T* tmp = dynamic_cast<T*>(e);
					if (tmp != nullptr) return tmp;
				}
				return nullptr;
			};

			template<class T> vector<T*> GetComponents()
			{
				vector<T*> components;
				FOREACH(e, this->components)
				{
					T* tmp = dynamic_cast<T*>(e);
					if (tmp != nullptr) components.push_back(tmp);
				}
				return components;
			};

			template<class T> static T* Instantiate(Object* parent)
			{
				T* child = new T();
				parent->children.push_back(child);
				child->parent = parent;
				child->name = "(Clone)";
				return child;
			};
		};
	}
}