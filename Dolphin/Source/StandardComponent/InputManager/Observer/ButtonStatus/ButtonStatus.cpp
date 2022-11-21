#include "ButtonStatus.h"

void Dolphin::StandardComponent::Input::ButtonStatus::Tick()
{
    // ボタンが押されたとき
    if (this->isPush)
    {
        this->isIdle = false;
        this->isPush = false;
        this->isHold = true;
        this->isPull = false;
    }

    // ボタンが離されたとき
    if (this->isPull)
    {
        this->isIdle = true;
        this->isPush = false;
        this->isHold = false;
        this->isPull = false;
    }
}

void Dolphin::StandardComponent::Input::ButtonStatus::Push()
{
    this->isPush = true;
}

void Dolphin::StandardComponent::Input::ButtonStatus::Pull()
{
    this->isPull = true;
}

bool Dolphin::StandardComponent::Input::ButtonStatus::IsIdle()
{
    return this->isIdle;
}

bool Dolphin::StandardComponent::Input::ButtonStatus::IsPush()
{
    return this->isPush;
}

bool Dolphin::StandardComponent::Input::ButtonStatus::IsHold()
{
    return this->isHold;
}

bool Dolphin::StandardComponent::Input::ButtonStatus::IsPull()
{
    return this->isPull;
}