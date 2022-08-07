#include "IInputHandler.h"

#if defined(_WINDOWS)
#include "Windows/WindowsInputHandler.h"
#endif

using tabi::IInputHandler;
using tabi::InputHandler;

IInputHandler& tabi::IInputHandler::GetInstance()
{
    static IInputHandler* instance = new InputHandler();

    return *instance;
}
