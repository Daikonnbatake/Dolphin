#include "Application.h"


DolphinCore::Application::Application()
{
	using namespace Dolphin::StandardComponent;
	this->quit = false;
	this->rootObject = ObjectBuilder::Instantiate("root")
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


void DolphinCore::Application::Tick()
{
	this->rootObject->Tick();
	this->Quit();
}


DolphinCore::Application::~Application()
{
	DELL(this->rootObject);
}


void DolphinCore::Application::Quit() { this->quit = true; }
bool DolphinCore::Application::IsQuit() { return this->quit; }