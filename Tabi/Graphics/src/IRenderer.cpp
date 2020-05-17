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
