#include "Application.h"


DolphinCore::Application::Application()
{
	this->rootObject = NEW("name");
	this->rootObject = nullptr;
	this->quit = false;
}


DolphinCore::Application::~Application()
{
	DELL(this->rootObject);
}


void DolphinCore::Application::Tick()
{
	this->rootObject->Tick();
}


void DolphinCore::Application::Quit() { this->quit = true; }
bool DolphinCore::Application::IsQuit() { return this->quit; }