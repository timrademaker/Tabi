#include "IWindow.h"

#if defined(_WINDOWS)
#include "Windows/OpenGL/OpenGLWindow.h"
#endif

tabi::shared_ptr<tabi::graphics::IWindow> tabi::graphics::IWindow::OpenWindow(const char* a_WindowName, unsigned int a_Width, unsigned int a_Height)
{
    return tabi::make_shared<Window>(a_WindowName, a_Width, a_Height);
}
