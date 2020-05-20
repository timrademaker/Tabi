#include "Windows/OpenGL/OpenGLContext.h"

#include <glad/glad.h>

using namespace tabi::graphics;

Context::Context(HWND a_Hwnd, unsigned a_Width, unsigned a_Height)
{
    Context::Resize(a_Width, a_Height);
    m_DeviceContext = GetDC(a_Hwnd);
}

void Context::SwapBuffer() const
{
    SwapBuffers(m_DeviceContext);
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Context::Resize(unsigned a_Width, unsigned a_Height)
{
    m_Witdh = a_Width;
    m_Height = a_Height;

    glViewport(0, 0, a_Width, a_Height);
}
