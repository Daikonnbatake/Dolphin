#include "Application.h"

C::Application::Application()
{
	this->rootObject = new Object("root");
}


C::Application::~Application()
{
	RELEASE(this->rootObject);
}


void C::Application::Initialize()
{
	TestObj* obj1 = Object::Instantiate<TestObj>(this->rootObject);
	Object::Instantiate<TestObj>(obj1);
	Object::Instantiate<TestObj>(obj1);
	Object::Instantiate<TestObj>(obj1);
	Object::Instantiate<TestObj>(obj1);
	obj1->AddComponent<TestComponent>();
	obj1->AddComponent<TestComponent>();
	this->test = obj1->AddComponent<TestComponent>();
	TestComponent* test1 = obj1->GetComponent<TestComponent>();
	vector<TestComponent*> test2 = obj1->GetComponents<TestComponent>();
	cout << "ready" << "\n";
}


void C::Application::Tick()
{
	cout << test->Hoge() << "\n";
	cout << test->Foo() << "\n";
}


void C::Application::Release()
{
	cout << "Release" << "\n";
}