#pragma comment(lib, "d2d1")
#pragma comment(lib, "windowscodecs.lib")
#include "Application.h"
#include "Dolphin.h"

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <windows.h>
#include <iostream>

namespace Dolphin
{
    /**************************************************************************
     *
     * オブジェクトツリーの定義.
     *
     *************************************************************************/
    Dolphin::Core::Object* InitObjectTree()
    {
        using namespace Dolphin::StandardComponent;

        return NEW(L"root")
            .AddComponent<InputManager>()
            .Child(
                NEW(L"ChildWindow1")
                    .AddComponent<Transform2D>()
                    .AddComponent<Window>()
                    .AddComponent<Direct2DRenderer>()
                    .Child(
                        NEW(L"Sprite1")
                        .AddComponent<Transform2D>()
                        .AddComponent<Direct2DSprite>()
                    )
            )
            .Child(NEW(L"ChildWindow2")
                       .AddComponent<Transform2D>()
                       .AddComponent<Window>()
                       .AddComponent<Direct2DRenderer>()
                       .Child(NEW(L"Sprite2")
                                  .AddComponent<Transform2D>()
                                  .AddComponent<Direct2DSprite>()
                       )
            )
            .Child(
                NEW(L"ChildWindow3")
                    .AddComponent<Transform2D>()
                    .AddComponent<Window>()
                    .AddComponent<Direct2DRenderer>()
                    .Child(
                        NEW(L"Sprite3")
                        .AddComponent<Transform2D>()
                        .AddComponent<Direct2DSprite>()
                    )
            );
    }


    /**************************************************************************
     *
     * アプリケーションの初期化処理.
     *
     *************************************************************************/
    void Start(Application& app)
    {
        auto root = app.Root();
        auto sprite1 = root->Nest()->GetChild(L"ChildWindow1")->Nest()->GetChild(L"Sprite1")->GetComponent<Direct2DSprite>();
        auto sprite2 = root->Nest()->GetChild(L"ChildWindow2")->Nest()->GetChild(L"Sprite2")->GetComponent<Direct2DSprite>();
        auto sprite3 = root->Nest()->GetChild(L"ChildWindow3")->Nest()->GetChild(L"Sprite3")->GetComponent<Direct2DSprite>();

        sprite1->ImagePath(L"../Dolphin/Application/Resource/dummy.png");
        sprite2->ImagePath(L"../Dolphin/Application/Resource/dummy.png");
        sprite3->ImagePath(L"../Dolphin/Application/Resource/dummy.png");
    }


    /**************************************************************************
     *
     * アプリケーションの内部更新処理.
     *
     *************************************************************************/
    void Update(Application& app)
    {
        auto rootWindow = app.Root()->Nest()->GetChild(L"ChildWindow1")->GetComponent<Window>();
        if (rootWindow->Closed())
            app.Quit();
    }


    /**************************************************************************
     *
     * アプリケーションの画面描画処理.
     *
     *************************************************************************/
    void Rendering(Application& app)
    {
    }


    /**************************************************************************
     *
     * アプリケーションの解放処理.
     *
     *************************************************************************/
    void Release(Application& app)
    {
    }
}


/******************************************************************************
 *
 * エントリーポイント.
 *
 ******************************************************************************/
int WINAPI WinMain(
    _In_ HINSTANCE     hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR         lpCmdLine,
    _In_ int           nCmdShow)
{
    Application app;
    Angle       a = Angle(50);
    double      b = a.Degree();

    while (!app.IsQuit()) { app.Tick(); }
    return 0;
}