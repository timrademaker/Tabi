#include "Windows/WindowsWindow.h"

#include "IRenderer.h"

#include <Logging.h>

#include <Application.h>

#include <Windows.h>
#include <GL/GL.h>

using namespace tabi::graphics;

const char* Window::ms_WindowClassName = "TabiWindowClass";

const char* tabi::graphics::Window::GetWindowClassName()
{
    return ms_WindowClassName;
}

bool Window::InitializeWindow(const char* a_WindowName, uint32_t a_Width, uint32_t a_Height)
{
    WindowHandle handle;
    {
        WNDCLASS wc = { 0 };
        // Window procedure function - Handles messages
        wc.lpfnWndProc = ProcessMessages;
        wc.hInstance = nullptr;
        wc.lpszClassName = ms_WindowClassName;
        wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wc.style = CS_OWNDC;

        if (!RegisterClass(&wc))
        {
            TABI_CRITICAL("Unable to register class for window creation!");
            TABI_ASSERT(false);
            return false;
        }

        handle = CreateWindowEx(0, wc.lpszClassName,
            a_WindowName,
            WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
            CW_USEDEFAULT, CW_USEDEFAULT, a_Width, a_Height,
            nullptr, nullptr, nullptr, nullptr
        );
    }

    m_WindowName = a_WindowName;
    m_WindowHandle = handle;

    return true;
}

LRESULT tabi::graphics::ProcessMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_CLOSE:
    {
        Application::Get().ExitGame();
        break;
    }
    case WM_SIZE:
    {
        const unsigned int width = LOWORD(lParam);
        const unsigned int height = HIWORD(lParam);

        IWindow::GetInstance().Resize(width, height);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
