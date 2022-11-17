#pragma once
#include "DolphinStd.h"
#include "Object/Object_member.h"
#include "ObjectBuilder_forward.h"
#include "BuilderChain/BuilderChain.h"


namespace Dolphin
{
	class ObjectBuilder
	{
	public:
		static BuilderChain Instantiate(string name);
	};
}