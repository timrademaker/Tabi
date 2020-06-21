#include "IWindow.h"

#if defined(_WINDOWS)
#include "Windows/WindowsWindow.h"
#endif

tabi::shared_ptr<tabi::graphics::IWindow> tabi::graphics::IWindow::OpenWindow(const char* a_WindowName, unsigned int a_Width, unsigned int a_Height)
{
    return tabi::make_shared<Window>(a_WindowName, a_Width, a_Height);
}

void tabi::graphics::IWindow::SwapBuffer() const
{
    if (m_Context)
    {
        m_Context->SwapBuffer();
    }
}

const char* tabi::graphics::IWindow::GetWindowName() const
{
    return m_WindowName;
}

tabi::graphics::WindowHandle tabi::graphics::IWindow::GetHandle() const
{
    return m_WindowHandle;
}

tabi::graphics::IContext* tabi::graphics::IWindow::GetContext() const
{
    return m_Context.get();
}