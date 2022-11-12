#pragma once

namespace Dolphin
{
	namespace Helper
	{
		// クラスを読み取り専用にする
		template<class Parent, class T>
		class ReadOnlyClass : public T
		{
		public:
			ReadOnlyClass() {};
			ReadOnlyClass(const T& v) : value(v) {}

		public:
			friend Parent;

		private:
			T value;
			T& operator=(const T& v) { value = v; return value; }
		};


		// プリミティブ型を読み取り専用にする
		template<class Parent, typename T>
		class ReadOnlyPrimitive
		{
		public:
			ReadOnlyPrimitive() {};
			ReadOnlyPrimitive(const T& v) : value(v) {}

		public:
			friend Parent;
			operator T() { return value; }

		private:
			T value;
			T& operator=(const T& v) { value = v; return value; }
		};
	}
}