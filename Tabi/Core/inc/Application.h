#pragma once

#include "GameBase.h"

#include <TabiPointers.h>

#include <IWindow.h>

namespace tabi
{
    class TABI_EXPORT Application
    {
    public:
    
        /**
        * Get the application
        * @return A reference to the application
        */
        static Application& Get();
    
        /**
        * Run the game
        * @param a_Game The user-defined game instance
        * @return The error code if an error occurred
        */
        int Run(tabi::shared_ptr<GameBase> a_Game);

        void ExitGame() { m_Running = false; }
    
    private:
        Application() {};
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
    
        void Initialize();

        void Destroy();

    private:
        tabi::shared_ptr<tabi::graphics::IWindow> m_Window;

        bool m_Running = false;

        bool m_Initialized = false;
    };
}
