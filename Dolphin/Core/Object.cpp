#include "Object.h"


DolphinCore::Object::Object(string name)
{
	this->name = name;
	this->onStart = true;
	this->isActive = true;
	this->components = new vector<Component*>();
}


void DolphinCore::Object::Start()
{
	FOREACH(e, *this->components) e->Start();
	this->onStart = false;
}


void DolphinCore::Object::Tick()
{
	if (!this->isActive) return;
	if (this->onStart) this->Start();
	FOREACH(e, *this->components) e->Tick();
}


DolphinCore::Object::~Object()
{
	FOREACH(e, *this->components) RELEASE(e);
	RELEASE(this->components);
}


bool				DolphinCore::Object::IsActive()	{ return this->isActive; }
void				DolphinCore::Object::Enable()	{ this->isActive = true; }
void				DolphinCore::Object::Disable()	{ this->isActive = false; }
std::string			DolphinCore::Object::Name()		{ return this->name; }


void DolphinCore::Object::PopComponent(Component* target)
{
	int componentCount = (int)this->components->size();
	FOR(i, componentCount)
	{
		if ((*this->components)[i] == target)
		{
			RELEASE(target);
			this->components->erase(this->components->begin() + i);
			return;
		}
	}
}


DolphinCore::Object* DolphinCore::Object::Instantiate(string name)
{
	return new Object(name);
}


void DolphinCore::Object::Destroy(Object* target)
{
	RELEASE(target);
}