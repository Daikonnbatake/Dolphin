#include "Application_member.h"

#include "DolphinStandardComponent.h"

Dolphin::Core::Application::Application()
{
	using namespace Dolphin::StandardComponent;
	this->quit = false;

	this->rootObject = New("root")
		.AddComponent<Transform2D>()
		.AddComponent<Window>()
		.Child(
			New("ObjectA")
			.AddComponent<Transform2D>()
			.AddComponent<Window>()
			.Child(
				New("ObjectAA")
				.AddComponent<Transform2D>()
				.AddComponent<Window>()
			)
			.Child(
				New("ObjectAB")
				.AddComponent<Transform2D>()
				.AddComponent<Window>()
				.Child(
					New("ObjectABA")
					.AddComponent<Transform2D>()
					.AddComponent<Window>()
				)
			)
		);
}


void Dolphin::Core::Application::Tick()
{
	this->rootObject->Tick();
	auto window = this->rootObject->GetComponent<Dolphin::StandardComponent::Window>();
	if (window->Closed())
	{
		this->Quit();
	}
}


Dolphin::Core::Application::~Application()
{
	DELL(this->rootObject);
}


void Dolphin::Core::Application::Quit() { this->quit = true; }
bool Dolphin::Core::Application::IsQuit() { return this->quit; }