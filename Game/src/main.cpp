// Entry point

#include <Application.h>
#include <GameBase.h>

#include <Logging.h>
#include <TabiLogger.h>
#include <TabiTypes.h>
#include <ConsoleSink.h>


int main()
{   
    tabi::logger::Log(tabi::logger::ELogLevel::Info, "Running game!");

    auto game = tabi::make_shared<tabi::GameBase>("Game", 640, 480, false);

    return tabi::Application::Get().Run(game);
}