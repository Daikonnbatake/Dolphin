#pragma once
#include "Core.h"

namespace Dolphin
{
	namespace Core
	{
		// 相互インクルード用プロトタイプ宣言
		class Object;

		class Component
		{
		// 隠しフィールド
		private:
			Object* parent;


		// コンストラクタ(object以外からのインスタンス化を許可しない)
		private:
			Component(Object* parent);


		// デストラクタ
		public:
			virtual ~Component(){};


		friend class Object;
		};
	}
}