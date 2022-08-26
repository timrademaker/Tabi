#include "IInputHandler.h"

#if defined(_WINDOWS)
#include "Windows/WindowsInputHandler.h"
#endif

tabi::IInputHandler* tabi::IInputHandler::CreateInstance()
{
    return new InputHandler{};
}
