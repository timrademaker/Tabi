#include <Application.h>
#include <GameBase.h>

#include <Logging.h>

#include <cassert>
#include <chrono>

#if defined(_WINDOWS)
#include "Windows/WindowsWindow.h"
#endif


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

        m_Window->SwapBuffer();

        auto frameEnd = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(frameEnd - frameStart).count();
        TabiLog(ELogLevel::Trace, "DeltaTime: " + std::to_string(deltaTime));

#if defined(_WINDOWS)
        MSG msg = MSG();
        while(PeekMessage(&msg, m_Window->GetHandle(), NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
#endif
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
        // Create window
        m_Window = graphics::IWindow::OpenWindow("Test Window", 640, 480);

        m_Initialized = true;
    }
}


void Application::Destroy()
{

}
