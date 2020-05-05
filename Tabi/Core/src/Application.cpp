#include <Application.h>
#include <GameBase.h>

#include <Logging.h>

#include <cassert>
#include <chrono>


using tabi::Application;
using tabi::GameBase;
using tabi::logger::ELogLevel;
using tabi::logger::TabiLog;



Application& Application::Get()
{
    static Application instance;
    instance.Initialize();

    return instance;
}

int Application::Run(tabi::shared_ptr<GameBase> a_Game)
{
    if (!a_Game->OnInitialize()) {
        TabiLog(ELogLevel::Error, "Failed to initialize game!");
        return 1;
    }

    m_Running = true;

    float deltaTime = 0.0f;
    while (m_Running)
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        a_Game->OnUpdate(deltaTime);

        // TODO: Update active scene?
        // TODO: Update subsystems

        // TODO: Render

        a_Game->OnRender();

        auto frameEnd = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(frameEnd - frameStart).count();
        TabiLog(ELogLevel::Trace, "DeltaTime: " + std::to_string(deltaTime));
    }
    
    TabiLog(ELogLevel::Trace, "Exited game loop");

    a_Game->OnDestroy();

    TabiLog(ELogLevel::Trace, "Returning from " + tabi::string(__FUNCTION__));
    return 0;
}

void Application::Initialize()
{
    if (!m_Initialized)
    {

        m_Initialized = true;
    }
}


void Application::Destroy()
{

}
