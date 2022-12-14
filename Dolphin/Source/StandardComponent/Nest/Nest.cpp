#include "pch.h"
#include "Nest.h"


Dolphin::StandardComponent::Nest::Nest(Dolphin::Core::Object* object)
    : Component(object)
{
    this->parent = nullptr;
}


Dolphin::StandardComponent::Nest::~Nest()
{
    FOREACH(e, this->children) Dolphin::Core::Object::Destroy(&e);
}


Dolphin::Core::Object* Dolphin::StandardComponent::Nest::Parent()
{
    return this->parent;
}
int Dolphin::StandardComponent::Nest::ChildCount()
{
    return (int)this->children.size();
}


Dolphin::Core::Object*
Dolphin::StandardComponent::Nest::MoveTo(Core::Object* target)
{
    Nest* nowParent = this->object->GetComponent<Nest>();
    Nest* newParent = target->GetComponent<Nest>();
    FOR(i, (int)nowParent->children.size())
    {
        if (nowParent->children[i] == this->object)
        {
            Dolphin::Core::Object::Destroy(&nowParent->children[i]);
            nowParent->children.erase(nowParent->children.begin() + i);
        }
    }

    this->parent = target;
    newParent->children.push_back(this->object);

    return nullptr;
}


Dolphin::Core::Object*
Dolphin::StandardComponent::Nest::AddChild(string name)
{
    Core::Object* child = NEW(name);
    return child->Nest()->MoveTo(this->object);
}


Dolphin::Core::Object* Dolphin::StandardComponent::Nest::GetChild(string name)
{
    FOREACH(e, this->children)
    {
        if (e->Name() == name)
            return e;
    }
    return nullptr;
}


void Dolphin::StandardComponent::Nest::Tick()
{
    int length = this->children.size();
    for (int i = 0; i < length; ++i)
    {
        if (this->children[i] == nullptr)
        {
            auto itr = this->children.begin() + i;
            this->children.erase(itr);
            --i;
            --length;
            continue;
        }
        // なんとか childern[i] を nullptr にできないかしら
        // それか deleted 判定したい
        this->children[i]->Tick();
        length = this->children.size();
    }
}