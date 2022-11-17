﻿#include "Object_member.h"
#include "DolphinMacro.h"
#include "Source/StandardComponent/Nest.h"


Dolphin::Core::Object::Object(string name)
{
	this->name = name;
	this->onStart = true;
	this->isActive = true;
	this->components = new vector<Component*>();
	this->nest = this->AddComponent<Dolphin::StandardComponent::Nest>();
}


void Dolphin::Core::Object::Start()
{
	FOREACH(e, *this->components) e->Start();
	this->onStart = false;
}


void Dolphin::Core::Object::Tick()
{
	if (!this->isActive) return;
	if (this->onStart) this->Start();
	FOREACH(e, *this->components) e->Tick();
}


Dolphin::Core::Object::~Object()
{
	FOREACH(e, *this->components) RELEASE(e);
	RELEASE(this->components);
}


bool				Dolphin::Core::Object::IsActive()	{ return this->isActive; }
void				Dolphin::Core::Object::Enable()		{ this->isActive = true; }
void				Dolphin::Core::Object::Disable()	{ this->isActive = false; }
std::string			Dolphin::Core::Object::Name()		{ return this->name; }
Dolphin::StandardComponent::Nest* Dolphin::Core::Object::Nest() { return this->nest; }


void Dolphin::Core::Object::PopComponent(Component* target)
{
	int componentCount = (int)this->components->size();
	FOR(i, componentCount)
	{
		if ((*this->components)[i] == target)
		{
			RELEASE(target);
			this->components->erase(this->components->begin() + i);
			break;
		}
	}
}


Dolphin::Core::Object* Dolphin::Core::Object::Instantiate(string name)
{
	return new Object(name);
}


void Dolphin::Core::Object::Destroy(Object* target)
{
	RELEASE(target);
}