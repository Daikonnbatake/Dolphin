#include "Nest.h"

DolphinSC::Nest::Nest(DolphinCore::Object* object) : Component(object)
{
	this->parent = this->object->GetComponent<Nest>()->object;
}


DolphinSC::Nest::~Nest()
{
	FOREACH(e, this->children) DELL(e);
}


DolphinCore::Object* DolphinSC::Nest::Parent() { return this->parent; }
int DolphinSC::Nest::ChildCount() { return (int)this->children.size(); }


DolphinCore::Object* DolphinSC::Nest::MoveTo(DolphinCore::Object* target)
{
	Nest* nowParent = this->object->GetComponent<Nest>();
	Nest* newParent = target->GetComponent<Nest>();
	FOR(i, nowParent->children.size())
	{
		if (nowParent->children[i] == this->object)
		{
			nowParent->children.erase(nowParent->children.begin() + i);
		}
	}

	this->parent = target;
	newParent->children.push_back(this->object);
}