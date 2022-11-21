#pragma once
#include "Dolphin.h"


namespace Dolphin
{
    class Application;
    Object*       InitObjectTree();
    void          Start(Application& app);
    void          Update(Application& app);
    void          Rendering(Application& app);
    void          Release(Application& app);

    class Application
    {
      private:
        Core::Object* rootObject;
        bool          quit;
        bool          init;
        void          Start();


      public:
        Application();
        ~Application();
        Dolphin::Core::Object* Root();
        void                   Tick();
        void                   Quit();
        bool                   IsQuit();
    };
}