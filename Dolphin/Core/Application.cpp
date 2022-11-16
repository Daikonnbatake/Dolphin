#include "Application.h"


DolphinCore::Application::Application()
{
	this->rootObject = NEW("name");
	this->quit = false;
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