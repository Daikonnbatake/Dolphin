#pragma once
#include "Core.h"

namespace Dolphin
{
	namespace Core
	{
		// ���݃C���N���[�h�p�v���g�^�C�v�錾
		class Object;

		class Component
		{
		// �B���t�B�[���h
		private:
			Object* parent;


		// �R���X�g���N�^(object�ȊO����̃C���X�^���X���������Ȃ�)
		private:
			Component(Object* parent);


		// �f�X�g���N�^
		public:
			virtual ~Component(){};


		friend class Object;
		};
	}
}