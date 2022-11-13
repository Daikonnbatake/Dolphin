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
}


void C::Application::Tick()
{
}


void C::Application::Release()
{
}