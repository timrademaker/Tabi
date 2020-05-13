#include "Windows/OpenGL/OpenGLContext.h"

using namespace tabi::graphics;

void Context::SwapBuffer() const
{
    SwapBuffers(m_DeviceContext);
}
