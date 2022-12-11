#pragma comment(lib, "d2d1")
#pragma comment(lib, "windowscodecs.lib")
#include "Application.h"
#include "Dolphin.h"

#include <chrono>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <windows.h>
#include <iostream>
#include <thread>

namespace Dolphin
{
    double degrees;

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
                    .AddComponent<DirectWriteText>()
                )
            )
            .Child(
                NEW(L"ChildWindow2")
                .AddComponent<Transform2D>()
                .AddComponent<Window>()
                .AddComponent<Direct2DRenderer>()
                .Child(
                    NEW(L"Sprite2")
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
        auto text = root->Nest()->GetChild(L"ChildWindow1")->Nest()->GetChild(L"Sprite1")->GetComponent<DirectWriteText>();

        sprite1->ImagePath(L"../../OtherResource/demo.png");
        //sprite1->Clipping(0, 16, 128, 64);
        sprite2->ImagePath(L"../../OtherResource/demo.png");
        sprite3->ImagePath(L"../../OtherResource/demo.png");
        sprite3->AffineTransform(AffineBuilder(sprite3->CropRect()).FlipX());

        degrees = 0;
    }


    /**************************************************************************
     *
     * アプリケーションの更新処理.
     *
     *************************************************************************/
    void Update(Application& app)
    {
        auto root = app.Root();
        auto window1 = root->Nest()->GetChild(L"ChildWindow1")->GetComponent<Window>();
        auto window2 = root->Nest()->GetChild(L"ChildWindow2")->GetComponent<Window>();
        auto window3 = root->Nest()->GetChild(L"ChildWindow3")->GetComponent<Window>();
        auto sprite1 = root->Nest()->GetChild(L"ChildWindow1")->Nest()->GetChild(L"Sprite1")->GetComponent<Direct2DSprite>();
        auto sprite2 = root->Nest()->GetChild(L"ChildWindow2")->Nest()->GetChild(L"Sprite2")->GetComponent<Direct2DSprite>();
        auto sprite3 = root->Nest()->GetChild(L"ChildWindow3")->Nest()->GetChild(L"Sprite3")->GetComponent<Direct2DSprite>();

        degrees = (degrees + 1L);
        RECT window1Rect;
        RECT window2Rect;
        RECT window3Rect;
        RECT client1Rect;
        GetWindowRect(window1->WindowHandle(), &window1Rect);
        GetWindowRect(window2->WindowHandle(), &window2Rect);
        GetWindowRect(window3->WindowHandle(), &window3Rect);
        GetClientRect(window1->WindowHandle(), &client1Rect);

        // window1 のクライアント領域の座標を取りたい
        int offsetX = (window1Rect.right - window1Rect.left) - (client1Rect.right - client1Rect.left);
        int offsetY = (window1Rect.bottom - window1Rect.top) - (client1Rect.bottom - client1Rect.top);

        AffineBuilder transform1 = AffineBuilder(sprite1->CropRect());
        AffineBuilder transform2 = AffineBuilder(sprite2->CropRect());
        AffineBuilder transform3 = AffineBuilder(sprite3->CropRect());

        transform1.Origin(0, 0).Translation(-window1Rect.left - offsetX, -window1Rect.top - offsetY);
        transform2.Origin(0, 0).Translation(-window2Rect.left - offsetX, -window2Rect.top - offsetY);
        transform3.Origin(0, 0).Translation(-window3Rect.left - offsetX, -window3Rect.top - offsetY);
        //transform2.Rotate(degrees);
        sprite1->AffineTransform(transform1);
        sprite2->AffineTransform(transform2);
        sprite3->AffineTransform(transform3);

        auto rootWindow = app.Root()->Nest()->GetChild(L"ChildWindow1")->GetComponent<Window>();
        if (rootWindow->Closed())
            app.Quit();
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

    //ゲーム処理のスレッド(ほぼ 60fps 固定)
    auto gameThread = std::thread(
    [&](){
            using namespace std::chrono;
            microseconds sleepTime = microseconds(16666);
            while (!app.IsQuit())
            {
                system_clock::time_point begin;
                system_clock::time_point end;

                begin = system_clock::now();
                app.Tick();
                end = system_clock::now();

                auto diff = end - begin;
                auto sleep = sleepTime - diff;
                //if (0 < sleep.count()) std::this_thread::sleep_for(sleepTime - diff);
            }
        }
    );

    //メッセージループ
    while (!app.IsQuit())
    {
        MSG message = { 0 };
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    gameThread.join();
    return 0;
}