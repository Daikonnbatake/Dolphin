/*****************************************************************//**
 * @file   Application.h
 * @brief  アプリケーションクラスの定義.
 *
 * @author かがまーる
 * @date   November 2022
 *********************************************************************/

#pragma once
#include "Core.h"
#include "Object.h"

namespace Dolphin
{
	namespace Core
	{
		/**
		* @brief WinMain からアプリケーション部分の処理を切り出すためのクラス.
		*/
		class Application
		{
		private:
			Object* rootObject; ///< root オブジェクトへのポインタ.


		public:
			/**
			* @brief コンストラクタ.
			*/
			Application();


			/**
			* @brief デストラクタ.
			*/
			~Application();


			/**
			* @brief 初期化処理.
			*/
			void Initialize();


			/**
			* @brief フレーム更新処理.
			*/
			void Tick();


			/**
			* @brief 終了処理.
			*/
			void Release();
		};
	}
}