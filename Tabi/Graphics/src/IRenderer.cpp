#include "IRenderer.h"

#if defined(_WINDOWS)
#include "Windows/OpenGL/OpenGLRenderer.h"
#endif


using namespace tabi::graphics;

IRenderer& IRenderer::GetInstance()
{
    static IRenderer* instance;
    if(!instance)
    {
        instance = new Renderer;
    }

    return *instance;
}

void tabi::graphics::IRenderer::UpdateWindowDimensions(unsigned int a_Width, unsigned int a_Height)
{
    m_WindowWidth = a_Width;
    m_WindowHeight = a_Height;
}

void tabi::graphics::IRenderer::GetWindowDimensions(unsigned int& a_Width, unsigned int& a_Height) const
{
    a_Width = m_WindowWidth;
    a_Height = m_WindowHeight;
}