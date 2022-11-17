#include "Component_member.h"

Dolphin::Core::Component::Component(Object* object)
{
	this->object = object;
}

Dolphin::Core::Object* Dolphin::Core::Component::ThisObject() { return this->object; }