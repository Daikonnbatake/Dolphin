#pragma once
#include "DolphinMacro.h"
#include "DolphinStd.h"
#include "Object_forward.h"
#include "Object_member.h"


template<class T> inline T* Dolphin::Core::Object::AddComponent()
{
    T* component = new T(this);
    this->components->push_back(component);
    return component;
}


template<class T> T* Dolphin::Core::Object::GetComponent()
{
    FOREACH(e, *this->components)
    {
        T* tmp = dynamic_cast<T*>(e);
        if (tmp != nullptr)
            return tmp;
    }
    return nullptr;
}


template<class T> std::vector<T*> Dolphin::Core::Object::GetComponents()
{
    vector<T*> components;
    FOREACH(e, *this->components)
    {
        T* tmp = dynamic_cast<T*>(e);
        if (tmp != nullptr)
            components.push_back(tmp);
    }
    return components;
}