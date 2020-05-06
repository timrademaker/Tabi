#include "IRenderer.h"

using namespace tabi::graphics;

IRenderer& IRenderer::GetInstance()
{
    static IRenderer* instance;
    if(!instance)
    {
        // TODO: Create instance        
    }

    return *instance;
}
