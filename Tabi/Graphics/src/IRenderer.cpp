#include "IRenderer.h"

#include "IWindow.h"

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

void tabi::graphics::IRenderer::Initialize(tabi::shared_ptr<IWindow> a_Window)
{
    m_Window = a_Window;
}

bool tabi::graphics::IRenderer::HasBeenInitialized() const
{
    return m_Initialized;
}

void tabi::graphics::IRenderer::UpdateWindowDimensions(unsigned int a_Width, unsigned int a_Height)
{
    if (m_Window)
    {
        //m_Window->GetContext()->Resize(a_Width, a_Height);
        TABI_ASSERT(false, "Deprecated");
    }
}

void tabi::graphics::IRenderer::GetWindowDimensions(unsigned int& a_Width, unsigned int& a_Height) const
{
    if (m_Window)
    {
        IWindow::GetInstance().GetWindowDimensions(a_Width, a_Height);
    }
}

const IWindow& tabi::graphics::IRenderer::GetWindow() const
{
    return *m_Window;
}