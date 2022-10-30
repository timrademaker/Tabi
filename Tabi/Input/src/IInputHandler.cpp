#include "IInputHandler.h"

#if defined(_WINDOWS)
#include "Windows/WindowsInputHandler.h"
#else
#error "No input method found for the current platform"
#endif

tabi::IInputHandler* tabi::IInputHandler::CreateInstance()
{
    return new InputHandler{};
}
