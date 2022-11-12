#include "Object.h"

C::Object::Object()
{
	this->parent = nullptr;
	this->children = vector<Object>();
	this->components = vector<Component>();
}


C::Object::Object(Object* parent)
{
	this->parent = parent;
	this->children = vector<Object>();
	this->components = vector<Component>();
}