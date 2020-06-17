#include "Windows/OpenGL/OpenGLContext.h"

#include "Windows/OpenGL/OpenGLHelpers.h"
#include "IRenderer.h"

#include <Logging.h>

#include <glad/glad.h>

using namespace tabi::graphics;

Context::Context(HWND a_Hwnd, unsigned a_Width, unsigned a_Height)
{
    m_DeviceContext = GetDC(a_Hwnd);

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

    const int letWindowsChooseThisPixelFormat = ChoosePixelFormat(m_DeviceContext, &pfd);
    SetPixelFormat(m_DeviceContext, letWindowsChooseThisPixelFormat, &pfd);

    HGLRC const openGLRenderingContext = wglCreateContext(m_DeviceContext);
    wglMakeCurrent(m_DeviceContext, openGLRenderingContext);

    if (!gladLoadGL())
    {
        logger::TabiLog(logger::ELogLevel::Warning, "Failed to initialize OpenGL context");
    }
#if defined(_DEBUG)
#if defined(GL_DEBUG_OUTPUT)
    tabi::graphics::helpers::EnableOpenGLDebugOutput();
#endif
#endif
    
    Context::Resize(a_Width, a_Height);
}

void Context::SwapBuffer() const
{
    SwapBuffers(m_DeviceContext);
    glClearColor(0.109f, 0.4218f, 0.8984f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Context::Resize(unsigned a_Width, unsigned a_Height)
{
    m_Witdh = a_Width;
    m_Height = a_Height;

    glViewport(0, 0, a_Width, a_Height);

    graphics::IRenderer::GetInstance().UpdateWindowDimensions(a_Width, a_Height);
}
