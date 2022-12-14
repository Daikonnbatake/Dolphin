#include "pch.h"
#include "DolphinMacro.h"
#include "Object_member.h"
#include "Source/StandardComponent/Nest/Nest.h"


Dolphin::Core::Object::Object(string name)
{
    this->name       = name;
    this->onStart    = true;
    this->isActive   = true;
    this->components = new vector<Component*>();
    this->nest       = this->AddComponent<Dolphin::StandardComponent::Nest>();
}


void Dolphin::Core::Object::Start()
{
    int length = this->components->size();
    for (int i = 0; i < length; ++i)
    {
        (*this->components)[length -i -1]->Start();
        length = this->components->size();
    }

    this->onStart = false;
}


void Dolphin::Core::Object::Tick()
{
    if (!this->isActive)
        return;
    if (this->onStart)
        this->Start();

    int length;
    length = this->components->size();

    for (int i = 0; i < length; ++i)
    {
        (*this->components)[length -i -1]->Tick();
        length = this->components->size();
    }
    
    length = this->components->size();

    for (int i = 0; i < length; ++i)
    {
        (*this->components)[length -i -1]->LateTick();
        length = this->components->size();
    }
}


Dolphin::Core::Object::~Object()
{
    FOREACH(e, *this->components) RELEASE(e);
    RELEASE(this->components);
}


bool         Dolphin::Core::Object::IsActive() { return this->isActive; }
void         Dolphin::Core::Object::Enable() { this->isActive = true; }
void         Dolphin::Core::Object::Disable() { this->isActive = false; }
std::wstring Dolphin::Core::Object::Name() { return this->name; }
Dolphin::StandardComponent::Nest* Dolphin::Core::Object::Nest()
{
    return this->nest;
}


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


void Dolphin::Core::Object::Destroy(Object** target)
{
    Object* tmp = *target;
    delete tmp;
    *target = nullptr;
    target = nullptr;
}