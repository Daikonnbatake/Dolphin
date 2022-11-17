#pragma once
#include "DolphinStd.h"
#include "Source/Core/Object/Object_member.h"
#include "BuilderChain/BuilderChain.h"
#include "ObjectBuilder_forward.h"
#define NEW(name) Dolphin::ObjectBuilder::Instantiate(name)


namespace Dolphin
{
	class ObjectBuilder
	{
	public:
		static BuilderChain Instantiate(string name);
	};
}