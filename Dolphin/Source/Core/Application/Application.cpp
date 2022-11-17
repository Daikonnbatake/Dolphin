#include "Application_member.h"

#include "DolphinStandardComponent.h"

Dolphin::Core::Application::Application()
{
	using namespace Dolphin::StandardComponent;
	this->quit = false;
	this->rootObject = New("root")
		.AddComponent<Transform2D>()
		.Child(
			New("ObjectA")
			.AddComponent<Transform2D>()
			.Child(
				New("ObjectAA")
				.AddComponent<Transform2D>()
			)
			.Child(
				New("ObjectAB")
				.AddComponent<Transform2D>()
			)
		)
		.Child(
			New("ObjectB")
			.AddComponent<Transform2D>()
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