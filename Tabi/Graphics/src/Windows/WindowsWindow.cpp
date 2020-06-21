#include "Windows/WindowsWindow.h"

#include "IRenderer.h"

#include <Logging.h>

#include <Application.h>

#include <glad/glad.h>

#include <Windows.h>
#include <GL/GL.h>

#if defined(OPENGL)
#include "Windows/OpenGL/OpenGLContext.h"
#endif

#pragma comment (lib, "opengl32.lib")

using namespace tabi::graphics;

const char* Window::ms_WindowClassName = "TabiWindowClass";

tabi::graphics::Window::Window(const char* a_WindowName, unsigned int a_Width, unsigned int a_Height)
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
            logger::TabiLog(logger::ELogLevel::Critical, "Unable to register class for window creation!");
            assert(false);
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
    m_Context = tabi::make_shared<Context>(handle, a_Width, a_Height);
}

const char* tabi::graphics::Window::GetWindowClassName()
{
    return ms_WindowClassName;
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
        unsigned int width = LOWORD(lParam);
        unsigned int height = HIWORD(lParam);
        IRenderer::GetInstance().UpdateWindowDimensions(width, height);

        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
