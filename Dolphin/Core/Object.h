/*****************************************************************//**
 * @file   Object.h
 * @brief  オブジェクトクラスの定義.
 *
 * @author かがまーる
 * @date   November 2022
 *********************************************************************/

#pragma once
#include "Core.h"
#include "Component.h"


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

			bool				isActive;		///< このオブジェクトがアクティブかどうか.
			Object*				parent;			///< このオブジェクトの親へのポインタ.
			string				name;			///< このオブジェクトの名前.
			vector<Object*>		children;		///< このオブジェクトが持つ子へのポインタ.
			vector<Component*>	components;		///< このオブジェクトが持つコンポーネントへのポインタ.

			Object() = delete; ///< 削除済み.


		public:

			/**
			* @brief コンストラクタ.
			* @param[in] name このオブジェクトの名前.
			*/
			Object(string name);


			/**
			* @brief
			* デストラクタ.\n
			* 継承先で必ずオーバーライドすること！(メモリリークの危険ｱﾘ).
			*/
			virtual ~Object();


			/**
			* @brief このオブジェクトがアクティブかどうかを返す.
			* @return このオブジェクトがアクティブなら true.
			*/
			bool IsActive();


			/**
			* @brief このオブジェクトが root オブジェクトかどうかを返す.
			* @return このオブジェクトが root オブジェクトなら true.
			*/
			bool IsRoot();


			/**
			* @brief
			* 親オブジェクトのポインタを返す.\n
			* root オブジェクトは自分自身を返す.
			* @return 親オブジェクトへのポインタ.
			*/
			Object* Parent();


			/**
			* @brief このオブジェクトの名前を返す.
			* @return このオブジェクトの名前.
			*/
			string Name();


			/**
			* @brief オブジェクトを削除する.
			* @param[in] target 対象オブジェクトへのポインタ.
			*/
			static void Destroy(Object* target);


			/**
			* @brief コンポーネントを削除する.
			* @param[in] target 対象コンポーネントへのポインタ.
			*/
			static void Destroy(Component* target);


			/**
			* @brief オブジェクトの比較.
			*/
			bool operator==(const Object& obj);


			/**
			* @brief オブジェクトの比較.
			*/
			bool operator!=(const Object& obj);


			/**
			 * @brief コンポーネントを追加する.
			 * @return 追加したコンポーネントのインスタンスへのポインタ.
			 */
			template<class T> T* AddComponent()
			{
				T* component = new T(this);
				this->components.push_back(dynamic_cast<Component*>(component));
				return component;
			};


			/**
			* @brief 指定した型に合致するコンポーネントの内, 一番最初に現れたコンポーネントを取得する.
			* @return 取得できた場合はコンポーネントへのポインタ, 出来なかった場合は nullptr.
			*/
			template<class T> T* GetComponent()
			{
				FOREACH(e, this->components)
				{
					T* tmp = dynamic_cast<T*>(e);
					if (tmp != nullptr) return tmp;
				}
				return nullptr;
			};


			/**
			* @brief 指定した型に合致するコンポーネントをすべて取得する.
			* @return コンポーネントへのポインタの配列.
			*/
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


			/**
			* @brief
			* 指定した型のオブジェクトを生成する.
			* 生成したオブジェクトは明示的に delete を実行しなければメモリが解放されないので注意.
			* @param[in] parent 親オブジェクトへのポインタ.
			* @return 生成したオブジェクトへのポインタ.
			*/
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