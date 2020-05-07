#pragma once

#include <TabiContainers.h>
#include <TabiPointers.h>

#if defined(_WINDOWS)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace tabi
{
    namespace graphics
    {
#if defined(_WINDOWS)
        using WindowHandle = HWND;
#endif
    }
}