/*****************************************************************//**
 * @file   Application.h
 * @brief  アプリケーションクラスの定義.
 *
 * @author かがまーる
 * @date   November 2022
 *********************************************************************/

#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"
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
			Object* rootObject;	///< root オブジェクトへのポインタ.
			bool	quit;		///< アプリケーションの終了判定.


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
			* @brief フレーム更新処理.
			*/
			void Tick();


			/**
			* @brief アプリケーションを終了させる.
			*/
			void Quit();


			/**
			* @brief アプリケーションの終了状態を取得する.
			* @return アプリケーションが終了しているなら true.
			*/
			bool IsQuit();
		};
	}
}