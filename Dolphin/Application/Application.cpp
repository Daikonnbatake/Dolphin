#include "Application.h"
#include "Core/ObjectBuilder.h"
#include "DolphinStandardComponent.h"

Dolphin::Application::Application()
{
	using namespace Dolphin::StandardComponent;
	this->quit = false;
	this->init = false;

	// オブジェクトツリーの定義
	this->rootObject = Dolphin::InitObjectTree();
}

void Dolphin::Application::Start()
{
	Dolphin::Start(*this);
	using namespace Dolphin::StandardComponent;
}


void Dolphin::Application::Tick()
{
	// Object.Start() は Object.Tick() の 1 回目に呼ばれるので Object.Tick() を優先して呼ぶ.
	this->rootObject->Tick();

	if (this->init)
	{
		// Tick 毎の処理
		Dolphin::Update(*this);
		Dolphin::Rendering(*this);
	}
	else
	{
		// 初期化
		this->Start();
		this->init = true;
	}
}


Dolphin::Application::~Application()
{
	DELL(this->rootObject);
	Dolphin::Release(*this);
}


void Dolphin::Application::Quit() { this->quit = true; }
bool Dolphin::Application::IsQuit() { return this->quit; }
Dolphin::Core::Object* Dolphin::Application::Root() { return this->rootObject; }