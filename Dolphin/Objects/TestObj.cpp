#include "TestObj.h"

void C::TestObj::OnInit()
{
	cout << "OnInit";
}

void C::TestObj::OnUpdate()
{
	cout << "OnUpdate";
}

void C::TestObj::OnRender()
{
	cout << "OnRender";
}

void C::TestObj::OnDestroy()
{
}

C::TestObj::~TestObj()
{
	cout << "OnDestroy";
}
