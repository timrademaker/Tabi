#include "Windows/OpenGL/OpenGLWindow.h"

#include "IRenderer.h"

#include <Logging.h>

#include <Application.h>

#include <glad/glad.h>

#include <Windows.h>
#include <GL/GL.h>

#pragma comment (lib, "opengl32.lib")

using namespace tabi::graphics;

tabi::graphics::Window::Window(const char* a_WindowName, unsigned int a_Width, unsigned int a_Height)
{
    WindowHandle handle;
    {
        const LPCSTR windowClassName = "TabiWindowClass";

        WNDCLASS wc = { 0 };
        // Window procedure function - Handles messages
        wc.lpfnWndProc = ProcessMessages;
        wc.hInstance = nullptr;
        wc.lpszClassName = windowClassName;
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
    m_Context = new Context(handle, a_Width, a_Height);

    Test();
}

void Window::Test()
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint buff;
    glGenBuffers(1, &buff);
    glBindBuffer(GL_ARRAY_BUFFER, buff);

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    auto shaderProgram = IRenderer::GetInstance().CreateShaderProgram("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");

    glUseProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    DrawShit();
}

void Window::DrawShit()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Window::~Window()
{
    delete m_Context;
}

LRESULT tabi::graphics::ProcessMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_CREATE:
    {
        PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            32,             // Color depth of the framebuffer.
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24,     // Number of bits in the depth buffer
            8,    // Number of bits in the stencil buffer
            0,
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        const HDC deviceContext = GetDC(hWnd);
        const int letWindowsChooseThisPixelFormat = ChoosePixelFormat(deviceContext, &pfd);
        SetPixelFormat(deviceContext, letWindowsChooseThisPixelFormat, &pfd);

        HGLRC const openGLRenderingContext = wglCreateContext(deviceContext);
        wglMakeCurrent(deviceContext, openGLRenderingContext);

        if (!gladLoadGL())
        {
            logger::TabiLog(logger::ELogLevel::Warning, "Failed to initialize OpenGL context");
        }
    }
    break;
    case WM_CLOSE:
    {
        Application::Get().ExitGame();
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
