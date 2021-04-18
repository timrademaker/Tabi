// Entry point

#if defined(SPACESHOOTER)
#include "SpaceShooter/SpaceShooterGameMode.h"
using GameModeClass = SpaceShooter::SpaceShooterGameMode;
#else
#include "TestGameMode.h"
using GameModeClass = TestGameMode;
#endif

#include <Application.h>

#include <Logging.h>
#include <TabiLogger.h>


int main()
{   
    tabi::logger::Log(tabi::logger::ELogLevel::Info, "Running game!");

    auto game = tabi::make_shared<GameModeClass>("Game", 1280, 720, false);

    return tabi::Application::Get().Run(game);
}