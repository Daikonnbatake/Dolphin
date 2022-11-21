#include "KeyboardObserver.h"
#include "DolphinMacro.h"

Dolphin::StandardComponent::Input::KeyboardObserver*
    Dolphin::StandardComponent::Input::KeyboardObserver::instance;


Dolphin::StandardComponent::Input::KeyboardObserver::KeyboardObserver()
{
    this->key                            = unordered_map<int, ButtonStatus>();
    FOR(keyCode, 256) this->key[keyCode] = ButtonStatus();
}


Dolphin::StandardComponent::Input::KeyboardObserver::~KeyboardObserver()
{}


void Dolphin::StandardComponent::Input::KeyboardObserver::UpdateButton(
    keyCode       keyCode,
    ButtonStatus& target)
{
    target.Tick();
    if (GetKeyState(keyCode) & 0x80)
        target.Push();

    else if (target.IsHold())
        target.Pull();
}


void Dolphin::StandardComponent::Input::KeyboardObserver::Tick()
{
    FOR(key, 256)
        this->UpdateButton(key, this->key[key]);
}


Dolphin::StandardComponent::Input::IButtonReader*
Dolphin::StandardComponent::Input::KeyboardObserver::KeyState(
    keyCode virtualKeyCode)
{
    return &this->key[virtualKeyCode];
}


Dolphin::StandardComponent::Input::KeyboardObserver*
Dolphin::StandardComponent::Input::KeyboardObserver::Initialize()
{
    KeyboardObserver::instance = new KeyboardObserver();
    return KeyboardObserver::instance;
}


void Dolphin::StandardComponent::Input::KeyboardObserver::Destroy()
{
    RELEASE(KeyboardObserver::instance);
}


Dolphin::StandardComponent::Input::KeyboardObserver*
Dolphin::StandardComponent::Input::KeyboardObserver::Instance()
{
    KeyboardObserver::instance = new KeyboardObserver();
    return KeyboardObserver::instance;
}