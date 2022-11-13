#include "Object.h"

C::Object::Object()
{
	this->parent = nullptr;
	this->name = "";
	this->children = vector<Object*>();
	this->components = vector<Component*>();
}


C::Object::Object(string name)
{
	this->parent = nullptr;
	this->name = name;
	this->children = vector<Object*>();
	this->components = vector<Component*>();
}


C::Object::~Object()
{
	FOREACH(e, this->children) RELEASE(e);
	FOREACH(e, this->components) RELEASE(e);
}


bool			C::Object::IsActive()	{ return this->isActive; }
bool			C::Object::IsRoot()		{ return this->parent == this; }
std::string		C::Object::Name()		{ return this-> name; }
C::Object*		C::Object::Parent()		{ return this->parent; }


void C::Object::Destroy(Object* target)
{
	RELEASE(target);
}


void C::Object::Destroy(Component* target)
{
	RELEASE(target);
}


bool C::Object::operator==(const Object& obj)
{
	return typeid(*this).name() == typeid(obj).name();
}


bool C::Object::operator!=(const Object& obj)
{
	return typeid(*this).name() != typeid(obj).name();
}