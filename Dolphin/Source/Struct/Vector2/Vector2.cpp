#include "Vector2.h"

Dolphin::Struct::Vector2::Vector2() : x(0), y(0){};
Dolphin::Struct::Vector2::Vector2(float x, float y) : x(x), y(y){};

float Dolphin::Struct::Vector2::X() { return this->x; }
float Dolphin::Struct::Vector2::Y() { return this->y; }
void Dolphin::Struct::Vector2::X(float x) { this->x = x; }
void Dolphin::Struct::Vector2::Y(float y) { this->y = y; }