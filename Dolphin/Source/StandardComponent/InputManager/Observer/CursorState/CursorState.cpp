#include "CursorState.h"

Dolphin::StandardComponent::Input::CursorState::CursorState()
{
	this->x = 0;
	this->y = 0;
}


Dolphin::StandardComponent::Input::CursorState::~CursorState() {}


void Dolphin::StandardComponent::Input::CursorState::X(int x) { this->x = x; }
void Dolphin::StandardComponent::Input::CursorState::Y(int y) { this->y = y; }
int Dolphin::StandardComponent::Input::CursorState::X() { return this->x; }
int Dolphin::StandardComponent::Input::CursorState::Y() { return this->y; }