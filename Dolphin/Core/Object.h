#pragma once
#include "Core.h"
#include "Component.h"

namespace Dolphin
{
	namespace Core
	{
		class Object
		{
		// �B���t�B�[���h
		private:
			Object* parent;
			vector<Object> children;
			vector<Component> components;


		// �ǂݎ���p�t�B�[���h
		public:
			ReadOnlyPrimitive<Object, Object*> Parent;


		// �R���X�g���N�^ & �f�X�g���N�^
		public:
			Object();
			Object(Object* parent);
			virtual ~Object(){};
		};
	}
}