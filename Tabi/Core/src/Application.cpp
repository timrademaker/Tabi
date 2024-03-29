#include <Application.h>
#include <GameBase.h>

#include <InputManager.h>
#include <IInputHandler.h>

#include <IDevice.h>
#include <ICommandList.h>

#include <Graphics.h>

#include <TabiImGui.h>

#include <Logging.h>

#include <chrono>

#if defined(_WINDOWS)
#include "Windows/WindowsInputHandler.h"
#endif

tabi::IDevice* s_Device = nullptr;

using tabi::Application;
using tabi::GameBase;
using tabi::logger::ELogLevel;
using tabi::logger::TabiLog;

Application& Application::Get()
{
    static Application instance;

    return instance;
}

int Application::Run(tabi::shared_ptr<GameBase> a_Game)
{
    Get().Initialize(a_Game->GetWindowName(), a_Game->GetWindowWidth(), a_Game->GetWindowHeight());

    if (!a_Game->OnInitialize()) {
        TABI_ERROR("Failed to initialize game!");
        return 1;
    }

    m_Running = true;

    const auto windowHandle = graphics::IWindow::GetInstance().GetHandle();

    float deltaTime = 0.0f;
    while (m_Running)
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        a_Game->OnUpdate(deltaTime);

        // TODO: Update active scene?
        // TODO: Update subsystems

        graphics::BeginFrame();

        tabi::imgui::NewFrame(deltaTime);

        a_Game->OnRender();

        tabi::imgui::EndFrame();

        graphics::EndFrame();

        InputManager::Update();

        auto frameEnd = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(frameEnd - frameStart).count();
        //TabiLog(ELogLevel::Trace, "DeltaTime: %f", deltaTime);

#if defined(_WINDOWS)
        MSG msg = MSG();
        while(PeekMessage(&msg, windowHandle, NULL, NULL, PM_REMOVE))
        {
            InputManager::HandleWindowMsg(&msg);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
#endif
    }
    
    TabiLog(ELogLevel::Trace, "Exited game loop");

    a_Game->OnDestroy();

    TabiLog(ELogLevel::Trace, "Returning from %s",__FUNCTION__);
    return 0;
}

void Application::Initialize(const char* a_WindowTitle, unsigned int a_Width, unsigned int a_Height)
{
    if (!m_Initialized)
    {
        // Create window
        graphics::IWindow::Initialize(a_WindowTitle, a_Width, a_Height);

        s_Device = tabi::IDevice::GetInstance();
        s_Device->Initialize(graphics::IWindow::GetInstance().GetHandle(), a_Width, a_Height);

        m_Initialized = true;

        tabi::imgui::Init();
    }
}


void Application::Destroy()
{
    tabi::imgui::Shutdown();

    graphics::IWindow::GetInstance().OnWindowResize().Unsubscribe(s_Device);
    s_Device->Finalize();
}
