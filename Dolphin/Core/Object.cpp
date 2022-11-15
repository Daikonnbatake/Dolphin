#include "Object.h"


// コンストラクタ
DolphinCore::Object::Object(string name)
{
	this->name = name;
	this->onStart = true;
	this->isActive = true;
	this->components = new vector<Component*>();
}


// 初めて tick が呼ばれたとき
void DolphinCore::Object::Start()
{
	FOREACH(e, *this->components) e->Start();
	this->onStart = false;
}


// tick が呼ばれたとき
void DolphinCore::Object::Tick()
{
	if (!this->isActive) return;
	if (this->onStart) this->Start();
	FOREACH(e, *this->components) e->Tick();
}


// デストラクタ
DolphinCore::Object::~Object()
{
	FOREACH(e, *this->components) RELEASE(e);
	RELEASE(this->components);
}


bool			DolphinCore::Object::IsActive()	{ return this->isActive; }
void			DolphinCore::Object::Enable()	{ this->isActive = true; }
void			DolphinCore::Object::Disable()	{ this->isActive = false; }
std::string		DolphinCore::Object::Name()		{ return this->name; }



template DolphinCore::Component* DolphinCore::Object::AddComponent();
template<class T> T* DolphinCore::Object::AddComponent()
{
	Component* component = new T(this);
	this->components->push_back(component);
	return component;
}


template DolphinCore::Component* DolphinCore::Object::GetComponent();
template<class T> T* DolphinCore::Object::GetComponent()
{
	FOREACH(e, *this->components)
	{
		T* tmp = dynamic_cast<T*>(e);
		if (tmp != nullptr) return tmp;
	}
	return nullptr;
}


template std::vector<DolphinCore::Component*> DolphinCore::Object::GetComponents();
template<class T> std::vector<T*> DolphinCore::Object::GetComponents()
{
	vector<T*> components;
	FOREACH(e, *this->components)
	{
		T* tmp = dynamic_cast<T*>(e);
		if (tmp != nullptr) components.push_back(tmp);
	}
	return components;
}


void DolphinCore::Object::PopComponent(Component* target)
{
	int componentCount = (int)this->components->size();
	FOR(i, componentCount)
	{
		if ((*this->components)[i] == target)
		{
			RELEASE(target);
			this->components->erase(this->components->begin() + i);
			return;
		}
	}
}


DolphinCore::Object* DolphinCore::Object::Instantiate(string name)
{
	return new Object(name);
}


void DolphinCore::Object::Destroy(Object* target)
{
	RELEASE(target);
}