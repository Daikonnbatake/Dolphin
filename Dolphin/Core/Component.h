/*****************************************************************//**
 * @file   Component.h
 * @brief  コンポーネントクラスの定義.
 *
 * @author かがまーる
 * @date   November 2022
 *********************************************************************/

#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"


namespace Dolphin
{
	namespace Core
	{
		// 相互インクルード用プロトタイプ宣言
		class Object;

		/**
		* @brief コンポーネントのベース.
		*/
		class Component
		{
		friend class Object;

		private:
			Object* object; ///< 親オブジェクトへのポインタ.


			Component(Object* parent);
			virtual void Start(){};
			virtual void Tick(){};
			virtual ~Component(){};
		};
	}
}