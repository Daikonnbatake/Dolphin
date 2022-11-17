#include "Transform2D.h"


Dolphin::StandardComponent::Transform2D::Transform2D(Dolphin::Core::Object* object) : Component(object)
{
	this->position = Dolphin::Struct::Vector2(0, 0);
	this->scale = Dolphin::Struct::Vector2(1, 1);
	this->rotate = Dolphin::Struct::Angle(0);
}


Dolphin::Struct::Vector2& Dolphin::StandardComponent::Transform2D::Position() { return this->position; }
Dolphin::Struct::Vector2& Dolphin::StandardComponent::Transform2D::Scale() { return this->scale; }
Dolphin::Struct::Angle& Dolphin::StandardComponent::Transform2D::Rotate() { return this->rotate; }


void Dolphin::StandardComponent::Transform2D::Position(Dolphin::Struct::Vector2& position)
{
	this->position.X(position.X());
	this->position.Y(position.Y());
}


void Dolphin::StandardComponent::Transform2D::Scale(Dolphin::Struct::Vector2& scale)
{
	this->scale.X(scale.X());
	this->scale.Y(scale.Y());
}


void Dolphin::StandardComponent::Transform2D::Rotate(Dolphin::Struct::Angle& rotate)
{
	this->rotate.Radian(rotate.Radian());
}