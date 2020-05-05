#pragma once

#include "GameBase.h"
#include "TabiTypes.h"

#include <memory>

namespace tabi
{
    class Application
    {
    public:
    
        /**
        * Get the application
        * @return A reference to the application
        */
        static TABI_EXPORT Application& Get();
    
        /**
        * Run the game
        * @param a_Game The user-defined game instance
        * @return The error code if an error occurred
        */
        TABI_EXPORT int Run(tabi::shared_ptr<GameBase> a_Game);
    
    private:
        Application() {};
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
    
        void Initialize();

        void Destroy();

        bool m_Running = false;

        bool m_Initialized = false;
    };
}
