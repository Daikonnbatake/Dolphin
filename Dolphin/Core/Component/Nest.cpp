#include "Nest.h"


DolphinSC::Nest::Nest(DolphinCore::Object* object) : Component(object)
{
	this->parent = nullptr;
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
			DELL(nowParent->children[i]);
			nowParent->children.erase(nowParent->children.begin() + i);
		}
	}

	this->parent = target;
	newParent->children.push_back(this->object);
	
	return nullptr;
}


DolphinCore::Object* DolphinSC::Nest::GetChild(string name)
{
	FOREACH(e, this->children)
	{
		if (e->Name() == name) return e;
	}
	return nullptr;
}