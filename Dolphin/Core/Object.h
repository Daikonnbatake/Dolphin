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
			Object* parent;
			vector<Object> children;
			vector<Component> components;


		// 読み取り専用フィールド
		public:
			ReadOnlyPrimitive<Object, Object*> Parent;


		// コンストラクタ & デストラクタ
		public:
			Object();
			Object(Object* parent);
			virtual ~Object(){};
		};
	}
}