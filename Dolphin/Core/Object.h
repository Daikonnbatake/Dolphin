/*****************************************************************//**
 * @file   Object.h
 * @brief  オブジェクトクラスの定義.
 *
 * @author かがまーる
 * @date   November 2022
 *********************************************************************/

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
		/**
		* @brief オブジェクトのベース.
		*/
		class Object
		{
		private:
			string				name;		///< このオブジェクトの名前.
			bool				onStart;	///< まだこのオブジェクトの Tick() が呼ばれていないなら true.
			bool				isActive;	///< このオブジェクトがアクティブなら true.
			vector<Component*>*	components;	///< このオブジェクトが持つコンポーネントへのポインタ.

			Object(string name);
			void Start();
			virtual ~Object();


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