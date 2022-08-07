#include "IWindow.h"

#if defined(_WINDOWS)
#include "Windows/WindowsWindow.h"
#endif

#include <TabiMacros.h>

tabi::graphics::IWindow* s_Window = nullptr;

void tabi::graphics::IWindow::Initialize(const char* a_WindowName, uint32_t a_Width, uint32_t a_Height)
{
    TABI_ASSERT(s_Window == nullptr, "Window has already been initialized");
    s_Window = new Window();
    if(!s_Window->InitializeWindow(a_WindowName, a_Width, a_Height))
    {
        TABI_ASSERT(false, "Failed to initialize window");
    }
}

tabi::graphics::IWindow& tabi::graphics::IWindow::GetInstance()
{
    TABI_ASSERT(s_Window != nullptr, "Window has not been initialized yet");
    return *s_Window;
}

const char* tabi::graphics::IWindow::GetWindowName() const
{
    return m_WindowName;
}

tabi::graphics::WindowHandle tabi::graphics::IWindow::GetHandle() const
{
    return m_WindowHandle;
}

void tabi::graphics::IWindow::Resize(uint32_t a_Width, uint32_t a_Height)
{
    m_Width = a_Width;
    m_Height = a_Height;

    m_OnWindowResizeEvent.Broadcast({ a_Width, a_Height });
}
