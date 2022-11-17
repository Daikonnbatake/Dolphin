#pragma once
#include "BuilderChain_forward.h"
#include "BuilderChain_member.h"


template<class T> inline Dolphin::BuilderChain& Dolphin::BuilderChain::AddComponent()
{
	this->object->AddComponent<T>();
	return *this;
};

template Dolphin::BuilderChain& Dolphin::BuilderChain::AddComponent<Dolphin::Core::Component>();