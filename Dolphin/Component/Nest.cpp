#include "Nest.h"


Dolphin::StandardComponent::Nest::Nest(Dolphin::Core::Object* object) : Component(object)
{
	this->parent = nullptr;
}


Dolphin::StandardComponent::Nest::~Nest()
{
	FOREACH(e, this->children) DELL(e);
}


Dolphin::Core::Object* Dolphin::StandardComponent::Nest::Parent() { return this->parent; }
int Dolphin::StandardComponent::Nest::ChildCount() { return (int)this->children.size(); }


Dolphin::Core::Object* Dolphin::StandardComponent::Nest::MoveTo(Dolphin::Core::Object* target)
{
	Nest* nowParent = this->object->GetComponent<Nest>();
	Nest* newParent = target->GetComponent<Nest>();
	FOR(i, (int)nowParent->children.size())
	{
		if (nowParent->children[i] == this->object)
		{
			DELL(nowParent->children[i]);
			nowParent->children.erase(nowParent->children.begin() + i);
		}
	}

	this->parent = target;
	newParent->children.push_back(this->object);

	return nullptr;
}


Dolphin::Core::Object* Dolphin::StandardComponent::Nest::GetChild(string name)
{
	FOREACH(e, this->children)
	{
		if (e->Name() == name) return e;
	}
	return nullptr;
}