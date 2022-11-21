#include "MouseObserver.h"


Dolphin::StandardComponent::Input::MouseObserver*
Dolphin::StandardComponent::Input::MouseObserver::instance;


Dolphin::StandardComponent::Input::MouseObserver::MouseObserver()
{
    this->position = CursorState();
    this->left     = ButtonStatus();
    this->middle   = ButtonStatus();
    this->right    = ButtonStatus();
}


Dolphin::StandardComponent::Input::MouseObserver::~MouseObserver() {}


void Dolphin::StandardComponent::Input::MouseObserver::UpdateButton(keyCode keyCode, ButtonStatus& target)
{
    target.Tick();
    if (GetAsyncKeyState(keyCode) & 0x80)
        target.Push();

    else if (target.IsHold())
        target.Pull();
}


void Dolphin::StandardComponent::Input::MouseObserver::Tick()
{
    this->UpdateButton(VK_LBUTTON, this->left);
    this->UpdateButton(VK_MBUTTON, this->middle);
    this->UpdateButton(VK_RBUTTON, this->right);

    POINT pos;

    if (GetCursorPos(&pos) == TRUE)
    {
        this->position.X(pos.x);
        this->position.Y(pos.y);
    }
}


Dolphin::StandardComponent::Input::ICursorStateReader*
Dolphin::StandardComponent::Input::MouseObserver::Position()
{
    return &this->position;
}


Dolphin::StandardComponent::Input::IButtonReader*
Dolphin::StandardComponent::Input::MouseObserver::Left()
{
    return &this->left;
}


Dolphin::StandardComponent::Input::IButtonReader*
Dolphin::StandardComponent::Input::MouseObserver::Middle()
{
    return &this->middle;
}


Dolphin::StandardComponent::Input::IButtonReader*
Dolphin::StandardComponent::Input::MouseObserver::Right()
{
    return &this->right;
}


Dolphin::StandardComponent::Input::MouseObserver*
Dolphin::StandardComponent::Input::MouseObserver::Initialize()
{
    return MouseObserver::instance = new MouseObserver();
}


Dolphin::StandardComponent::Input::MouseObserver*
Dolphin::StandardComponent::Input::MouseObserver::Instance()
{
    return MouseObserver::instance;
}


void Dolphin::StandardComponent::Input::MouseObserver::Destroy()
{
    RELEASE(MouseObserver::instance);
}