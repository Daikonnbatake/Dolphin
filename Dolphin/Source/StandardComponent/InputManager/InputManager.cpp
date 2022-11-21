#include "InputManager.h"

#include <iostream>


Dolphin::StandardComponent::InputManager::InputManager(Core::Object* object)
    : Component(object)
{
    this->keyboardObserver = Input::KeyboardObserver::Initialize();
    this->mouseObserver    = Input::MouseObserver::Initialize();
}


Dolphin::StandardComponent::InputManager::~InputManager()
{
    Input::KeyboardObserver::Destroy();
    Input::MouseObserver::Destroy();
    this->keyboardObserver = nullptr;
    this->mouseObserver    = nullptr;
}


void Dolphin::StandardComponent::InputManager::Tick()
{
    this->keyboardObserver->Tick();
    this->mouseObserver->Tick();
}


Dolphin::StandardComponent::Input::IMouseReader*
Dolphin::StandardComponent::InputManager::MouseStatus()
{
    return this->mouseObserver;
}


Dolphin::StandardComponent::Input::IKeyboardReader*
Dolphin::StandardComponent::InputManager::KeyboardStatus()
{
    return this->keyboardObserver;
}