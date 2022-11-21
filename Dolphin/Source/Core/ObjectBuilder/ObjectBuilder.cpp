#include "ObjectBuilder_member.h"


Dolphin::BuilderChain Dolphin::ObjectBuilder::Instantiate(string name)
{
    return BuilderChain(Dolphin::Core::Object::Instantiate(name));
};