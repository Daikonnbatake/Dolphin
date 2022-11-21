#include "Angle.h"

Dolphin::Struct::Angle::Angle() { this->radian = 0; }
Dolphin::Struct::Angle::Angle(double degree)
{
    this->radian = ToRadian(degree);
}

double Dolphin::Struct::Angle::Radian() { return this->radian; }
double Dolphin::Struct::Angle::Degree() { return this->ToDegree(this->radian); }
void   Dolphin::Struct::Angle::Radian(double radian) { this->radian = radian; }
void   Dolphin::Struct::Angle::Degree(double degree)
{
    this->radian = ToRadian(degree);
}
double Dolphin::Struct::Angle::ToRadian(double degree)
{
    return degree * (Dolphin::Struct::pi / 180.0f);
}
double Dolphin::Struct::Angle::ToDegree(double radian)
{
    return radian * (180.0f / Dolphin::Struct::pi);
}