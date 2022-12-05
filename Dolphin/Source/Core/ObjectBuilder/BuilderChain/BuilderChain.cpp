#include "pch.h"
#include "BuilderChain.h"


Dolphin::BuilderChain::BuilderChain(Dolphin::Core::Object* object)
{
    this->object = object;
    this->nest   = this->object->Nest();
}


Dolphin::BuilderChain::operator Dolphin::Core::Object*()
{
    return this->object;
};


Dolphin::BuilderChain& Dolphin::BuilderChain::Child(BuilderChain& obj)
{
    obj.object->Nest()->MoveTo(this->object);
    return *this;
}