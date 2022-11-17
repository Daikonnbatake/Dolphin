#include "Application_member.h"


Dolphin::Core::Application::Application()
{
	using namespace Dolphin::StandardComponent;
	this->quit = false;
	this->rootObject = New("root")
		.AddComponent<Component>()
		.AddComponent<Component>()
		.Child(
			New("ObjectA")
			.AddComponent<Component>()
			.AddComponent<Component>()
			.AddComponent<Component>()
			.Child(
				New("ObjectAA")
				.AddComponent<Component>()
				.AddComponent<Component>()
			)
			.Child(
				New("ObjectAB")
				.AddComponent<Component>()
				.AddComponent<Component>()
			)
		)
		.Child(
			New("ObjectB")
			.AddComponent<Component>()
			.AddComponent<Component>()
			.AddComponent<Component>()
		);
}


void Dolphin::Core::Application::Tick()
{
	this->rootObject->Tick();
	this->Quit();
}


Dolphin::Core::Application::~Application()
{
	DELL(this->rootObject);
}


void Dolphin::Core::Application::Quit() { this->quit = true; }
bool Dolphin::Core::Application::IsQuit() { return this->quit; }