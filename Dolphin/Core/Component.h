/*****************************************************************//**
 * @file   Component.h
 * @brief  コンポーネントクラスの定義.
 *
 * @author かがまーる
 * @date   November 2022
 *********************************************************************/

#pragma once
#include "Core.h"


namespace Dolphin
{
	namespace Core
	{
		class Object; // 相互インクルード用プロトタイプ宣言

		/**
		* @brief コンポーネントのベース.
		*/
		class Component
		{
		private:
			Object* parent; ///< 親オブジェクトへのポインタ.


			/**
			* @brief
			* コンストラクタ.\n
			* Object クラスからのみインスタンス化が可能.
			* @param[in] parent 親オブジェクトへのポインタ.
			*/
			Component(Object* parent);


		public:

			/**
			* @brief
			* デストラクタ.\n
			* 継承先で必ずオーバーライドすること！(メモリリークの危険ｱﾘ).
			*/
			virtual ~Component(){};

		friend class Object;
		};
	}
}