#pragma once

namespace Dolphin
{
	namespace Helper
	{
		// �N���X��ǂݎ���p�ɂ���
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


		// �v���~�e�B�u�^��ǂݎ���p�ɂ���
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