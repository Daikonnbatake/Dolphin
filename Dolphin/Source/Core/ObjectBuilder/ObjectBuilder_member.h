#pragma once
#include "DolphinStd.h"
#include "Core/Object.h"
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