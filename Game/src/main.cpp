// Entry point

#include "TestGameMode.h"

#include <Application.h>

#include <Logging.h>
#include <TabiLogger.h>


int main()
{   
    tabi::logger::Log(tabi::logger::ELogLevel::Info, "Running game!");

    auto game = tabi::make_shared<TestGameMode>("Game", 1280, 720, false);

    return tabi::Application::Get().Run(game);
}